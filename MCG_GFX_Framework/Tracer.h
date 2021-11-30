#ifndef _TRACE_
#define _TRACE_

#include <cmath>

#include "MCG_GFX_Lib.h"

#include <vector>

#include "Sphere.h"
#include "Ray.h"
#include "SphereIntersection.h"
#include "Light.h"

class Tracer
{
protected:

	SphereIntersection sIntersect;

public:

	glm::vec3 rayTrace(Ray _ray, std::vector<Sphere>* _sVec, glm::vec3 _camPos, Light *_light, glm::vec3 backgroundColor);

	glm::vec3 closestPtOnLine(Ray _ray, glm::vec3 _pt);

	SphereIntersection sphereIntersect(Ray _ray, Sphere _sphere);

	glm::vec3 mapColor(glm::vec3 _col, int _map);
};


#endif