#ifndef _MAIN_
#define _MAIN_

#include <cmath>

#include "MCG_GFX_Lib.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

#include "Camera.h"
#include "Ray.h"
#include "Tracer.h"
#include "Sphere.h"
#include "Light.h"
#include "Mesh.h"


enum Axis {x, y, z};//for rotations

// Variable for storing window dimensions
glm::ivec2 windowSize(320, 240);

std::vector<Sphere> sVec;//vector of spheres
std::vector<Mesh> mVec;//vector of meshes

Camera *Cam;//the camera, creates rays
Tracer *Trace;//checks for intersections
Light *L;//point light source

void animate(Sphere *_sph, Axis _axis);//moves the spheres around an axis
void menu();//main menu

void rayTracerSphereAnimation();//fixed camera, rotating spheres
void rayTracerCameraAnimation();//fixed spheres, rotating camera
void drawCircle();//draws a circle pixel by pixel using trig
void drawSquare();//draws a square pixel by pixel using nested loops
void drawTriangle();//draws a triangle pixel by pixel using nested loops
void animated2D();//draws all 3 2D shapes and animates them
//updates the pixelColours vector within the passed range after calling the raytracing functions
void calculateColour(glm::ivec2& _startPos, glm::ivec2& _endpos, glm::vec3& _backgroundColor, std::shared_ptr<std::vector<std::vector<glm::vec3>>> _pixelColours);


#endif