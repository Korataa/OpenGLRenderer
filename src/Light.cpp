#include "../include/Light.h"

Light::Light(glm::vec3 position, glm::vec3 color) : color(color)
{
	this->position = position;
}