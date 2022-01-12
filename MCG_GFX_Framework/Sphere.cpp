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
