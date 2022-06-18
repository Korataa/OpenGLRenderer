#pragma once

#include <GLFW/glfw3.h>
#include "Shader.h"

class Renderer
{
public:
	
private:
	GLFWwindow* window;
	Shader shader;

	const float vertices[] = {
	-0.5f, -0.5f, 0.0f,	//left
	 0.5f, -0.5f, 0.0f,	//right
	 0.0f,  0.5f, 0.0f,	//top
	};
	
	//Buffers
	unsigned int VBO, VAO;
};