#ifndef _OBJ_
#define _OBJ_

#include <cmath>

#include "MCG_GFX_Lib.h"

#include "Ray.h"
#include "Light.h"

enum surfaceType { Rough, Smooth, Reflective}; //used for different types of shading
//Rough -> diffuse shading 
//Smooth -> diffuse + specular shading
//Reflective -> spawning reflection rays, making the object mirror like

class GameObject//base class for objects/Shapes... Currently only spheres are derived from it
{
protected:

	glm::vec3 Color; //color of the object

	surfaceType surfType;// the surface type of the object

public:
	GameObject();//empty default constructor

	GameObject(glm::vec3 _c, surfaceType _sType);//constructor

	virtual glm::vec3 Shade(Light _light, glm::vec3 _intersection, glm::vec3 _camPos) = 0; //function is to be overriden in the derived classes

	//setters
	void setColor(glm::vec3 _color);
	void setSurfType(surfaceType _sType);

	//getters
	glm::vec3 getColor();
	surfaceType getSurfType();

};


#endif
