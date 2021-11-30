#ifndef _OBJ_
#define _OBJ_

#include <cmath>

#include "MCG_GFX_Lib.h"

#include "Ray.h"
#include "Light.h"

enum surfaceType { Rough, Smooth, Reflective};

class GameObject
{
protected:

	glm::vec3 Color;

	surfaceType surfType;

public:
	GameObject();

	GameObject(glm::vec3 _c, surfaceType _sType);

	virtual glm::vec3 Shade(Light _light, glm::vec3 _intersection, glm::vec3 _camPos) = 0;

	void setColor(glm::vec3 _color);
	void setSurfType(surfaceType _sType);

	glm::vec3 getColor();
	surfaceType getSurfType();

};


#endif
