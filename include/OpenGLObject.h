#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
};

class OpenGLObject
{
public:
	glm::mat4 model;	//matrix to translate to world-coords
	glm::vec3 position;
	
	std::vector<

	OpenGLObject(const glm::vec3& position, const std::vector<GLfloat>& vertices);
	OpenGLObject(const float x, const float y, const float z, const std::vector<GLfloat>& vertices);
	OpenGLObject();
};