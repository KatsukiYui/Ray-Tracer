#ifndef _TRIANGLE_
#define _TRIANGLE_

#include "GameObject.h"

class Triangle
{

protected:


public:

	Triangle();//constructor

	//setters

	//getters


	virtual glm::vec3 Shade(Light _light, glm::vec3 _intersection, glm::vec3 _camPos);//shading function that is overriding the gameobject's function

};


#endif