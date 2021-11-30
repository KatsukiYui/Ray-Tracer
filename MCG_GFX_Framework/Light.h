#ifndef _LIGHT_
#define _LIGHT_

#include <cmath>

#include "MCG_GFX_Lib.h"



class Light

{
protected:
	glm::vec3 Position;

	glm::vec3 Color;

public:

	glm::vec3 getPos();
	glm::vec3 getCol();

	void setPos(glm::vec3 _pos);
	void setCol(glm::vec3 _col);

};

#endif // !_LIGHT_
