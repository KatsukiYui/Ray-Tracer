#include "Light.h"


glm::vec3 Light::getPos() { return Position; };
glm::vec3 Light::getCol() { return Color; };

void Light::setPos(glm::vec3 _pos) { Position = _pos; };
void Light::setCol(glm::vec3 _col) { Color = _col; };