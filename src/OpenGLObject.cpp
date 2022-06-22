#include "../include/OpenGLObject.h"

#include <glm/gtc/matrix_transform.hpp>

OpenGLObject::OpenGLObject(const glm::vec3& position, const std::vector<GLfloat>& vertices) : position(position), vertices(vertices)
{
	this->model = glm::mat4(1.0);
	this->model = glm::translate(model, position);
}

OpenGLObject::OpenGLObject(const float x, const float y, const float z, const std::vector<GLfloat>& vertices) : vertices(vertices)
{
	this->position = glm::vec3(x, y, z);
	this->model = glm::mat4(1.0);
	this->model = glm::translate(model, position);

}

OpenGLObject::OpenGLObject()
{
	model = glm::mat4(0.0f);
	position = glm::vec3(0.0f);

}

