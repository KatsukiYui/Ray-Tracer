#include "GameObject.h"

GameObject::GameObject()//default constructor
{
}

GameObject::GameObject(glm::vec3 _c, surfaceType _sType)//constructor that sets the properties
{
	Color = _c;
	surfType = _sType;
}

//setters
void GameObject::setColor(glm::vec3 _color) { Color = _color; };
void GameObject::setSurfType(surfaceType _sType) { surfType = _sType; };

//getters
glm::vec3 GameObject::getColor() { return Color; };
surfaceType GameObject::getSurfType() { return surfType; }


