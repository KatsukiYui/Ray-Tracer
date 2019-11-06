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

Camera *Cam;//the camera, creates rays
Tracer *Trace;//checks for intersections
Light *L;//point light source

void Animate(Sphere *_sph, Axis _axis);//moves the spheres around an axis
void Menu();//main menu

void RayTracerSphereAnimation();//fixed camera, rotating spheres
void RayTracerCameraAnimation();//fixed spheres, rotating camera
void drawCircle();//draws a circle pixel by pixel using trig
void drawSquare();//draws a square pixel by pixel using nested loops
void drawTriangle();//draws a triangle pixel by pixel using nested loops
void Animated2D();//draws all 3 2D shapes and animates them


#endif