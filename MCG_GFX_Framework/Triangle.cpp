#include "Triangle.h"

Triangle::Triangle(glm::vec3 _positions[3], glm::vec3 _normals[3])
{
	setPositions(_positions);
	seNormals(_normals);
}

void Triangle::setPositions(glm::vec3 _positions[3])
{
	for (int i = 0; i < 3; i++)
	{
		Positions[i] = _positions[i];

	}
}

void Triangle::seNormals(glm::vec3 _normals[3])
{
	for (int i = 0; i < 3; i++)
	{
		Normals[i] = _normals[i];

	}
}

glm::vec3* Triangle::getPositions()
{
	return Positions;
}

glm::vec3* Triangle::getNormals()
{
	return Normals;
}

