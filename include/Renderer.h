#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "Shader.h"

class Renderer
{
public:
	Renderer();

	int InitOpenGL();
	bool StartRendering();
	bool StopRendering();
	void destroy();
	
private:
	GLFWwindow* window;
	Shader shader;

	//all the vertices
	std::vector<GLfloat> vertices = {
		-0.5f, -0.5f, 0.0f,	//left
		 0.5f, -0.5f, 0.0f,	//right
		 0.0f,  0.5f, 0.0f,	//top
	};
	
	//Buffers
	unsigned int VBO, VAO;

private:
	bool isRunning;
};