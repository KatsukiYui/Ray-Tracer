#include "Tracer.h"

/*This function takes in a ray(created by the camera), the vector of spheres, camera position, light and background color
  This function loops through the vector and calls the sphere intersection function. It then uses the returned structure
  to return the appropriate color. If there is an intersection a shadow ray is sent, if it hits, return black
  else if the surface is reflective send a reflection ray (returns color of hit object or background color)
  otherwise return call the object's shading function and return that color after mapping it.
  If there wasnt an intersection to begin with, return background color
*/
glm::vec3 Tracer::rayTrace(Ray _ray, std::vector<Sphere>*_sVec, glm::vec3 _camPos, Light *_light, glm::vec3 backgroundColor)
{
	double shortestDis = 500000.0;//just a huge number by default

	glm::vec3 rayIntersection{ 0.0f, 0.0f, 0.0f }; //used for intersection checks

	int index = -1;//index of current sphere with the shortest distance (from ray origin to the 1st intersection pt)

	bool rayHit = false;//first ray intersection

	bool shadowHit = false;//shadow ray intersection

	bool reflectionHit = false;//reflection ray intersection for reflective objects


	for (int v = 0; v < _sVec->size(); v++)
	{
		sIntersect = sphereIntersect(_ray, (*_sVec)[v]);

		if (sIntersect.Hit)
		{
			rayHit = true;
			sIntersect.Hit = false;

			if (sIntersect.Distance < shortestDis) //finds the shortest distance
			{
				shortestDis = sIntersect.Distance;
				index = v;//saves its index within the vector and the 1st intersection pt
				rayIntersection = sIntersect.Intersection1;

			}
		}

	}

	if (rayHit == false)
	{
		return backgroundColor; //return background color if there wasnt an intersection
	}
	else if (rayHit == true)
	{
		//if the 1st ray intersected (there is a sphere in this pixel), send a shadow ray

		glm::vec3 Normal = rayIntersection - _sVec->at(index).getCentre(); //getting the normal at the 1st intersection pt

		Normal = glm::normalize(Normal);

		//shadow ray
		glm::vec3 sOrg = rayIntersection + Normal * 0.05F; //setting the shadow ray origin slightly away from the sphere 
		                                                   //shadow bias to avoid self insertion

		//sending a shadow ray to the tracer function to check for itnersections with any other sphere
		Ray shadowRay(sOrg, glm::normalize(_light->getPos() - sOrg));
		//added a small value to prevent the ray's origin from being inside the circle(shadow bias)

		//shadow intersection checks
		for (int p = 0; p < _sVec->size(); p++)
		{
			sIntersect = sphereIntersect(shadowRay, _sVec->at(p));//intersection check with shadow ray

			if (sIntersect.Hit == true)
			{
				shadowHit = true;
				sIntersect.Hit = false;
			}
		}


		if (shadowHit == true)//there is a shadow
		{	
			return glm::vec3(0, 0, 0);//return black
		}

		else if (shadowHit == false)//if the shadow ray doesnt collide with an object
		{
			//reflection ray
			if (_sVec->at(index).getSurfType() == Reflective) //is it a refelctive surface?
			{
				glm::vec3 Reflection = _ray.getDir() - 2 * glm::dot(Normal, _ray.getDir())*Normal; //the reflection ray dir which is a unit vector

				glm::vec3 rOrg = rayIntersection + Reflection * 0.05F; //adding a reflection bias to avoid self insertion

				Ray reflectionRay(rOrg, Reflection);

				int refIndex = 0;//used to index the object that the reflection ray hits, that also ahs the shortest distance from ray origin

				glm::vec3 refIntersect{ 0.0f, 0.0f, 0.0f };//used to do ray sphere intersection checks

				float refShortestDis = 500000.0;//used to dermine the shortest distance so only the closest object is reflected

				//reflection ray intersection checks
				for (int p = 0; p < _sVec->size(); p++)
				{
					sIntersect = sphereIntersect(reflectionRay, _sVec->at(p));//check for intersection

					if (sIntersect.Hit == true)
					{
						reflectionHit = true; //there was an intersection
						sIntersect.Hit = false;


						if (sIntersect.Distance < shortestDis) //finds the shortest distance
						{
							shortestDis = refShortestDis;

							refIndex = p;//save the index of the object with the shortest distance and the 1st intersection with it for shading

							refIntersect = sIntersect.Intersection1;

						}

					}

				}

				if (reflectionHit == true) //there is an object to reflect .. call that object's shading function and return the color
				{

					return 0.8F * mapColor(_sVec->at(refIndex).Shade(*_light, refIntersect, _camPos), 2); //dimming the color a bit


				}
				else if (reflectionHit == false)//reflect background color
				{
					return 0.8F * backgroundColor; //return background color (a bit dimmed out so u can see the object)
				}

			}
			//it is not a reflective surface and the shadow ray didnt collide with another object
			//call this object's shading function and return its color at that pt
			return mapColor(_sVec->at(index).Shade(*_light, rayIntersection, _camPos), 2);
		}

	}

};


//returns the closest pt on a ray from _pt
glm::vec3 Tracer::closestPtOnLine(Ray _ray, glm::vec3 _pt)
{

	return _ray.getOrg() + ((float)glm::dot(_pt - _ray.getOrg(), _ray.getDir())) * _ray.getDir();

	//a+((P-a).n)n  a is origin of ray.. n is direction (unit vec) .. P is the point thats not on the line (centre of the sphere in this case)
};

//checks for intersection between ray and sphere
SphereIntersection Tracer::sphereIntersect(Ray _ray, Sphere _sphere)
{
	SphereIntersection sphInt; //structure to be returned

	sphInt.Hit = false; //no intersection by default

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
			the ray origin
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
			//the closest pt is behind the camera
			sphInt.Hit = false;
		}


	}

	return sphInt; //return the structure
};

//map the color from 0-255 to 0-1 and back.. to be used for the shading function
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
