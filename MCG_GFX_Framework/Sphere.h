#ifndef _SPHERE_
#define _SPHERE_

#include "GameObject.h"



class Sphere: public GameObject
{

protected:

	glm::vec3 Centre;//centre of the sphere

	double Radius;//radius of the sphere


public:

	Sphere(glm::vec3 _cntr, double _r, glm::vec3 _clr, surfaceType _sType);//constructor

	//setters
	void setCentre(glm::vec3 _centre);
	void setRadius(double _radius);

	//getters
	glm::vec3 getCentre();
	double getRadius();


	virtual glm::vec3 Shade(Light _light, glm::vec3 _intersection, glm::vec3 _camPos);//shading function that is overriding the gameobject's function

};


#endif