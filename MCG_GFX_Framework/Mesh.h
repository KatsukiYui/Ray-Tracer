#ifndef _MESH_
#define _MESH_

#include "Triangle.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


//stores and manages a vector of triangles

class Mesh : public GameObject
{

protected:

	glm::vec3 Position;//position of the centre of model
	glm::quat Rotation;
	glm::vec3 Scale;
	std::vector<Triangle> Triangles;//vector of triangles that make up the model

public:

	Mesh(glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale, glm::vec3 _color, surfaceType _sType, std::string _filename);//constructor

	//setters
	void setPosition(glm::vec3 _position);
	void setRotation(glm::quat _rotation);
	void setScale(glm::vec3 _scale);

	//getters
	Triangle getTriangle(int _index);
	glm::vec3 getPosition();
	glm::quat getRotation();
	glm::vec3 getScale();
	int getTrianglesSize();

	void loadOBJ(std::string _filename);//OBJ Loader

	//shading function.. for now just returns the colour of the mesh..
	glm::vec3 Shade(Light _light, glm::vec3 _intersection, glm::vec3 _camPos);

	glm::vec3 multiplyByModelMatrix(glm::vec3 _point);
};


#endif