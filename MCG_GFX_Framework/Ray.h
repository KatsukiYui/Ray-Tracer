#ifndef _RAY_

#define _RAY_

#include <cmath>

#include "MCG_GFX_Lib.h"

class Ray
{
private:

	glm::vec3 Origin;//origin of the ray
	glm::vec3 Direction;//direction of the ray (normalized vec3)


public:
	Ray(glm::vec3 _org, glm::vec3 _dir);//constructor

	//setters
	void setOrg(glm::vec3 _org);
	void setDir(glm::vec3 _dir);
	//getters
	glm::vec3 getOrg();
	glm::vec3 getDir();


};


#endif