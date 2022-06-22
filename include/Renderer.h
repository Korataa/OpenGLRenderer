#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "Shader.h"
#include "Camera.h"
#include "OpenGLObject.h"

class Renderer
{
public:
	Renderer();

	bool initOpenGL();
	bool startRendering();
	bool stopRendering();
	void destroy();

public:
	glm::mat4 projection;	//projection matrix for clip space
	
private:
	GLFWwindow* window;
	Shader shader;
	Camera camera;

	std::vector<OpenGLObject> objects;
	
	//Buffers
	unsigned int VBO, VAO;
	bool isRunning;
	float deltaTime, lastFrame;

private:
	void processInput(GLFWwindow* window);
};