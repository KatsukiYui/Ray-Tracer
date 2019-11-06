#include "Light.h"


Light::Light()//defualt constructor
{
}

Light::Light(glm::vec3 _pos, glm::vec3 _col) //constructor setting the properties of the light object
{
	Position = _pos;
	Color = _col;
}

//getters
glm::vec3 Light::getPos() { return Position; };
glm::vec3 Light::getCol() { return Color; };

//setters
void Light::setPos(glm::vec3 _pos) { Position = _pos; };
void Light::setCol(glm::vec3 _col) { Color = _col; };