#include "Ray.h"

Ray::Ray(glm::vec3 _org, glm::vec3 _dir)
{
	Origin = _org;
	Direction = _dir;
}


void Ray::setOrg(glm::vec3 _org)
{
	Origin = _org;
};

void Ray::setDir(glm::vec3 _dir)
{
	Direction = _dir;
};

glm::vec3 Ray::getOrg()
{
	return Origin;
};

glm::vec3 Ray::getDir()
{
	return Direction;
};
