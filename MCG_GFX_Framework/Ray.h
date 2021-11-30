#ifndef _RAY_

#define _RAY_

#include <cmath>

#include "MCG_GFX_Lib.h"

class Ray
{
private:

	glm::vec3 Origin;
	glm::vec3 Direction;


public:
	Ray(glm::vec3 _org, glm::vec3 _dir);

	void setOrg(glm::vec3 _org);
	void setDir(glm::vec3 _dir);

	glm::vec3 getOrg();
	glm::vec3 getDir();


};


#endif