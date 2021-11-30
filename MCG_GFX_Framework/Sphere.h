#ifndef _SPHERE_
#define _SPHERE_

#include "GameObject.h"



class Sphere: public GameObject
{

protected:

	glm::vec3 Centre;

	double Radius;


public:

	Sphere(glm::vec3 _cntr, double _r, glm::vec3 _clr, surfaceType _sType);

	void setCentre(glm::vec3 _centre);
	void setRadius(double _radius);


	glm::vec3 getCentre();
	double getRadius();


	virtual glm::vec3 Shade(Light _light, glm::vec3 _intersection, glm::vec3 _camPos);

};


#endif