#pragma once

#include <glm/glm.hpp>
#include "OpenGLObject.h"

class Light : public OpenGLObject
{
public:
	Light(glm::vec3 position, glm::vec3 color);
	
	glm::vec3 color;
private:

};