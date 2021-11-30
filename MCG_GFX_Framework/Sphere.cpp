#include "Sphere.h"

Sphere::Sphere(glm::vec3 _cntr, double _r, glm::vec3 _clr, surfaceType _sType)//constructor
{
	Centre = _cntr;
	Radius = _r;
	Color = _clr;
	surfType = _sType;

}


//getters
void Sphere::setCentre(glm::vec3 _centre) { Centre = _centre; };
void Sphere::setRadius(double _radius) { Radius = _radius; };

//setters
glm::vec3 Sphere::getCentre() { return Centre; };
double Sphere::getRadius() { return Radius; };


//shading function.. applies diffuse and specular shading depending on the object's surface type
glm::vec3 Sphere::Shade(Light _light, glm::vec3 _intersection, glm::vec3 _camPos)
{

	glm::vec3 Normal(0, 0, 0);//normal to the surface at the intersection pt

	glm::vec3 PttoLight(0, 0, 0);//vector from the intersection pt to the light

	Normal = _intersection - Centre; //getting the normal at the 1st intersection pt

	Normal = glm::normalize(Normal);

	PttoLight = _light.getPos() - _intersection; //vector from the intersection pt to the light source

	PttoLight = glm::normalize(PttoLight);

	glm::vec3 reColor; //color to be returned

	switch (surfType)
	{
	case Rough:
		
		//Diffuse lighting for rough surfaces
		reColor = Color * _light.getCol() * (glm::max(glm::dot(Normal, PttoLight), 0.0f));
		//change if overflow
		reColor.x = glm::min(reColor.x, 1.0F);
		reColor.y = glm::min(reColor.y, 1.0F);
		reColor.z = glm::min(reColor.z, 1.0F);


		return reColor;

		break;

	case Smooth:

		//Specular lighting & diffuse for smooth surfaces

		glm::vec3 PttoCam(0, 0, 0);//vector from 1st intersection pt to the camera

		PttoCam = glm::normalize(_camPos - _intersection);

		glm::vec3 Halfway(0, 0, 0);

		Halfway = glm::normalize(PttoLight + PttoCam);//the halfway vector.. used to get the reflection ray's direction

		float Facing = 0;

		if ((glm::dot(Normal, PttoLight) > 0)) //stops specular lighting on surfaces that face away from the light
		{
			Facing = 1;
		}
		else
		{
			Facing = 0;
		}

		glm::vec3 Spec = Color * _light.getCol() * Facing * float(glm::pow((glm::max(glm::dot(Normal, Halfway), 0.0f)), 20)); //specular part
		glm::vec3 Diff = Color * _light.getCol() * (glm::max(glm::dot(Normal, PttoLight), 0.0f));//diffuse part

		reColor = Spec + Diff; //add them to get the return color

		//avoid overflow
		reColor.x = glm::min(reColor.x, 1.0F);
		reColor.y = glm::min(reColor.y, 1.0F);
		reColor.z = glm::min(reColor.z, 1.0F);

		return reColor;

		break;
	}
}
