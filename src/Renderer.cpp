#include "../include/Renderer.h"

#include <glad/glad.h>

#include <iostream>

const std::string vShaderPath = "resources/shaders/shader.vert";
const std::string fShaderPath = "resources/shaders/shader.frag";

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

Renderer::Renderer() : shader(vShaderPath, fShaderPath)
{ 

}

int Renderer::InitOpenGL()
{
	//Initialize glfw and configure it!
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create an openGL window
	this->window = glfwCreateWindow(800, 600, "My 3D Renderer", NULL, NULL);
	if (this->window == NULL)
	{
		//Failed to create window so we terminate glfw and handle other closing stuff
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(this->window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	//Glad
	//load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);

	//we copy our vertices vector into a buffer so openGL can use it
	//&vertices[0] points to the first element of the vector and vectors in c++ are stored contiguously
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	//vertex attrib pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
}

bool Renderer::StartRendering()
{
	if (isRunning)
	{
		//we return because 
		return false;
	}
	this->isRunning = true;
	//Main loop
	while (isRunning)
	{
		//Blah blah main loop stuff
	}
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}