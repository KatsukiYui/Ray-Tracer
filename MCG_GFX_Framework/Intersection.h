#ifndef _INTERSECT_
#define _INTERSECT_

#include <cmath>

#include "MCG_GFX_Lib.h"

struct Intersection//is returned by the tracer's intersection check function
{
	bool Hit = false; //is true if there is an intersection

	double Distance = 0.0;//distance between ray origin and intersection pt

	glm::vec3 Intersection1{ 0.0f, 0.0f, 0.0f };//first intersection

	glm::vec3 Intersection2{ 0.0f, 0.0f, 0.0f };//2nd intersection pt.. if there is any

};


#endif // !_INTERSECT_
