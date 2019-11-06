#ifndef _LIGHT_
#define _LIGHT_

#include <cmath>

#include "MCG_GFX_Lib.h"



class Light

{
protected:
	glm::vec3 Position;//position of the light in world space

	glm::vec3 Color;//color of the light

public:

	Light(); // default constructor
	Light(glm::vec3 _pos, glm::vec3 _col);//constructor

	//getters
	glm::vec3 getPos();
	glm::vec3 getCol();

	//setters
	void setPos(glm::vec3 _pos);
	void setCol(glm::vec3 _col);

};

#endif // !_LIGHT_
