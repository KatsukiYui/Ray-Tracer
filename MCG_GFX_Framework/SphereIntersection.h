#ifndef _SINT_
#define _SINT_

#include <cmath>

#include "MCG_GFX_Lib.h"

struct SphereIntersection
{
	bool Hit = false;

	double Distance = 0.0;

	glm::vec3 Intersection1;

	glm::vec3 Intersection2;

};


#endif // !_SINT_
