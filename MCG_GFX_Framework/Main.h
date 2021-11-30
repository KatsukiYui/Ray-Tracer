#ifndef _MAIN_
#define _MAIN_

#include <cmath>

#include "MCG_GFX_Lib.h"

#include <vector>
#include <iostream>
#include <sstream>

#include "Camera.h"
#include "Ray.h"
#include "Tracer.h"
#include "Sphere.h"
#include "Light.h"

enum Axis {x, y, z};//for rotations

// Variable for storing window dimensions
glm::ivec2 windowSize(640, 480);

std::vector<Sphere> sVec;//vector of spheres

Camera *Cam;
Tracer *Trace;
Light *L;

void Animate(Sphere *_sph, Axis _axis);//moves the spheres around an axis
void Menu();
void RayTracerSphereAnimation();
void RayTracerCameraAnimation();
void drawCircle();
void drawSquare();
void drawTriangle();


#endif