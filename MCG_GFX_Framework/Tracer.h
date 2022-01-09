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

public:

	/*This function takes in a ray(created by the camera), the vector of spheres, camera position, light and background color
	  This function loops through the vector and calls the sphere intersection function. It then uses the returned structure
	  to return the appropriate color. If there is an intersection a shadow ray is sent, if it hits, return black
	  else if the surface is reflective send a reflection ray (returns color of hit object or background color)
	  otherwise return call the object's shading function and return that color after mapping it.
	  If there wasnt an intersection to begin with, return background color
	*/
	glm::vec3 rayTrace(Ray _ray, std::vector<Sphere>* _sVec, glm::vec3 _camPos, Light *_light, glm::vec3 backgroundColor);

	glm::vec3 antiAliasing(Ray _ray1, Ray _ray2, std::vector<Sphere>* _sVec, glm::vec3 _camPos, Light* _light, glm::vec3 backgroundColor);

	glm::vec3 closestPtOnLine(Ray _ray, glm::vec3 _pt); //returns the closest pt on a ray from _pt

	SphereIntersection sphereIntersect(Ray _ray, Sphere _sphere); //checks for intersection between ray and sphere

	glm::vec3 mapColor(glm::vec3 _col, int _map); //map the color from 0-255 to 0-1 and back

};


#endif