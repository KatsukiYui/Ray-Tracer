#include "Tracer.h"


glm::vec3 Tracer::rayTrace(Ray _ray, std::vector<Sphere>*_sVec, glm::vec3 _camPos, Light *_light, glm::vec3 backgroundColor)
{
	double shortestDis = 500000.0;

	glm::vec3 rayIntersection;

	int index = -1;

	bool rayHit = false;

	bool shadowHit = false;

	bool reflectionHit = false;


	for (int v = 0; v < _sVec->size(); v++)
	{
		sIntersect = sphereIntersect(_ray, (*_sVec)[v]);

		if (sIntersect.Hit == true)
		{
			rayHit = true;

			if (sIntersect.Distance < shortestDis) //finds the shortest distance
			{
				shortestDis = sIntersect.Distance;
				index = v;
				rayIntersection = sIntersect.Intersection1;


			}
		}

	}

	if (rayHit == false)
	{
		return backgroundColor; //return background color
	}
	else if (rayHit == true)
	{

		glm::vec3 Normal = rayIntersection - _sVec->at(index).getCentre(); //getting the normal at the 1st intersection pt

		Normal = glm::normalize(Normal);

		//shadow ray
		glm::vec3 sOrg = rayIntersection + Normal * 0.05F; //setting the shadow ray origin slightly away from the sphere

		//sending a shadow ray to the tracer function
		Ray shadowRay(sOrg, glm::normalize(_light->getPos() - sOrg));
		//added a small value to prevent the ray's origin from being inside the circle

		//shadow intersection checks
		for (int p = 0; p < _sVec->size(); p++)
		{
			sIntersect = sphereIntersect(shadowRay, _sVec->at(p));

			if (sIntersect.Hit == true)
			{
				shadowHit = true;
			}
		}


		if (shadowHit == true)//there is a shadow
		{	
			return glm::vec3(0, 0, 0);
		}

		else if (shadowHit == false) //call the objects shading function and return the color
		{
		
			//reflection ray
			if (_sVec->at(index).getSurfType() == Reflective) //is it a refelctive surface?
			{
				glm::vec3 Reflection = _ray.getDir() - 2 * glm::dot(Normal, _ray.getDir())*Normal; //the reflection ray dir which is a unit vector

				glm::vec3 rOrg = rayIntersection + Reflection * 0.05F; //adding a reflection bias

				Ray reflectionRay(rOrg, Reflection);

				int refIndex = 0;

				glm::vec3 refIntersect;

				float refShortestDis = 5000;

				//reflection ray intrsection checks
				for (int p = 0; p < _sVec->size(); p++)
				{
					sIntersect = sphereIntersect(reflectionRay, _sVec->at(p));

					if (sIntersect.Hit == true)
					{
						reflectionHit = true;



						if (sIntersect.Distance < shortestDis) //finds the shortest distance
						{
							shortestDis = refShortestDis;

							refIndex = p;

							refIntersect = sIntersect.Intersection1;

						}

					}

				}

				if (reflectionHit == true) //there is an object to reflect .. call that object's shading function and return the color
				{


					//intersection checks for the other object

					return 0.8F * mapColor(_sVec->at(refIndex).Shade(*_light, refIntersect, _camPos), 2); //dimming the color a bit


				}
				else if (reflectionHit == false)//reflect background color
				{
					return 0.8F * backgroundColor; //return background color
				}

			}

			return mapColor(_sVec->at(index).Shade(*_light, rayIntersection, _camPos), 2);
		}

	}

};


glm::vec3 Tracer::closestPtOnLine(Ray _ray, glm::vec3 _pt)
{

	return _ray.getOrg() + ((float)glm::dot(_pt - _ray.getOrg(), _ray.getDir())) * _ray.getDir();

	//a+((P-a).n)n  a is origin of ray.. n is direction (unit vec) .. P is the point thats not on the line (centre of the sphere in this case)
};

SphereIntersection Tracer::sphereIntersect(Ray _ray, Sphere _sphere)
{
	SphereIntersection sphInt;

	sphInt.Hit = false;

	if (glm::length(_sphere.getCentre() - _ray.getOrg()) < _sphere.getRadius())
	{
		//is the ray origin inside the sphere??
		sphInt.Hit = false;
	}

	else
	{
		//gets (P-a).n aka length from org of ray to X (closest pt)
		float lenOrgtoX = glm::dot(_sphere.getCentre() - _ray.getOrg(), _ray.getDir());

		glm::vec3 X = closestPtOnLine(_ray, _sphere.getCentre());

		if (lenOrgtoX >= 0)
		{
			/*is the closest point behind or infront of the ray origin:
			we use dot product to get that length (P - a).n 
			where p is the centre of the sphere, a is origin of the ray and n is the direction of the ray (unit vector).
			If the length from the origin of the ray to X (the closest point) is -ve that means X is behind
			the ra origin
			*/

			glm::vec3 XtoP = _sphere.getCentre() - (X);

			//where X is the closest point on the ray to the centre of the circle P 
			//rule is vector from X to P = P - X -> P - a - ((p - a).n)*n
			//centre of circle is P .. X is calculated from that and the ray 
			
			double Distance = glm::length(XtoP); //distance between X and P 

			if (Distance == _sphere.getRadius())
			{
				//do they insterset??

				sphInt.Hit = true;

				//there is one intersection .. X is on the edge of the sphere

				sphInt.Intersection1 = X; //the intersection is the closest point

				sphInt.Intersection2 = X; //Z here is equal to 0 since the radius is equal to the shortest distance

				sphInt.Distance = glm::length(sphInt.Intersection1 - _ray.getOrg()); 
				//distance from ray origin to the intersection pt

			}

			else if (Distance < _sphere.getRadius())
			{
				sphInt.Hit = true;

				//there are two intersections .. X is inside the sphere

				double Z = glm::sqrt(glm::pow(_sphere.getRadius(), 2) - glm::pow(Distance, 2)); //as if the shortest distance vec, the radius and Z are a rightangled triangle

				sphInt.Intersection1 = _ray.getOrg() + (float)(lenOrgtoX - Z) * _ray.getDir();

				sphInt.Intersection2 = _ray.getOrg() + (float)(lenOrgtoX + Z) * _ray.getDir();

				sphInt.Distance = glm::length(sphInt.Intersection1 - _ray.getOrg());
				//distance from ray origin to the intersection pt

			}

			else if (Distance > _sphere.getRadius())
			{
				//there are no intersections ... X is outside the sphere

				sphInt.Hit = false;
			}

		}

		else
		{
			sphInt.Hit = false;
		}


	}

	return sphInt;
};


glm::vec3 Tracer::mapColor(glm::vec3 _col , int _map)
{
	//mapping a RGB color from 0 - 255 to 0 - 1
	switch (_map)
	{
	case 1:
		return _col /= 255;
		break;
	case 2:
		return _col *= 255; //changing it back
		break;
	}
};
