#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(glm::vec3 _c, surfaceType _sType)
{
	Color = _c;
	surfType = _sType;
}

void GameObject::setColor(glm::vec3 _color) { Color = _color; };
void GameObject::setSurfType(surfaceType _sType) { surfType = _sType; };

glm::vec3 GameObject::getColor() { return Color; };
surfaceType GameObject::getSurfType() { return surfType; }


