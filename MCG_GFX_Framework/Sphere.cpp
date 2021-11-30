#include "Sphere.h"

Sphere::Sphere(glm::vec3 _cntr, double _r, glm::vec3 _clr, surfaceType _sType)
{
	Centre = _cntr;
	Radius = _r;
	Color = _clr;
	surfType = _sType;

}



void Sphere::setCentre(glm::vec3 _centre) { Centre = _centre; };
void Sphere::setRadius(double _radius) { Radius = _radius; };


glm::vec3 Sphere::getCentre() { return Centre; };
double Sphere::getRadius() { return Radius; };

glm::vec3 Sphere::Shade(Light _light, glm::vec3 _intersection, glm::vec3 _camPos)
{

	glm::vec3 Normal(0, 0, 0);

	glm::vec3 PttoLight(0, 0, 0);

	Normal = _intersection - Centre; //getting the normal at the 1st intersection pt

	Normal = glm::normalize(Normal);

	PttoLight = _light.getPos() - _intersection; //vector from the intersection pt to the light source

	PttoLight = glm::normalize(PttoLight);

	glm::vec3 x;
	glm::vec3 reColor;

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

		glm::vec3 PttoCam(0, 0, 0);

		PttoCam = glm::normalize(_camPos - _intersection);

		glm::vec3 Halfway(0, 0, 0);

		Halfway = glm::normalize(PttoLight + PttoCam);

		float Facing = 0;

		if ((glm::dot(Normal, PttoLight) > 0))
		{
			Facing = 1;
		}
		else
		{
			Facing = 0;
		}

		glm::vec3 Spec = Color * _light.getCol() * Facing * glm::pow((glm::max(glm::dot(Normal, Halfway), 0.0f)), 20);
		glm::vec3 Diff = Color * _light.getCol() * (glm::max(glm::dot(Normal, PttoLight), 0.0f));

		reColor = Spec + Diff;

		reColor.x = glm::min(reColor.x, 1.0F);
		reColor.y = glm::min(reColor.y, 1.0F);
		reColor.z = glm::min(reColor.z, 1.0F);

		return reColor;

		break;
	}
}
