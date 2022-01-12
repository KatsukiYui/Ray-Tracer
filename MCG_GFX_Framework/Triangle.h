#ifndef _TRIANGLE_
#define _TRIANGLE_

#include "GameObject.h"

class Triangle
{

protected:
	//sticking to old coding standard in sphere.h
	glm::vec3 Positions[3];
	glm::vec3 Normals[3];

public:

	Triangle(glm::vec3 _positions[3], glm::vec3 _normals[3]);//constructor

	//setters
	void setPositions(glm::vec3 _positions[3]);
	void seNormals(glm::vec3 _normals[3]);

	//getters
	glm::vec3* getPositions();
	glm::vec3* getNormals();

};


#endif