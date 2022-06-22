#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../include/Shader.h"
#include "../include/Renderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

const std::string vShaderPath = "resources/shaders/shader.vert";
const std::string fShaderPath = "resources/shaders/shader.frag";

int main()
{
	Renderer renderer;
	if (!renderer.initOpenGL())
	{
		std::cout << "Something went wrong when loading the renderer!" << std::endl;
		return -1;
	}

	if (!renderer.startRendering())
	{
		std::cout << "Renderer already running or something went wrong" << std::endl;
		return -1;
	}
	else
	{
		std::cout << "Renderer closed or shut down" << std::endl;
		renderer.destroy();
	}
	return 0;
}

int main3()
{
	//glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//GLFW window creation
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad:load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shader(vShaderPath, fShaderPath);

	//set up our vertex data and buffers and configure vertex attributes
	const float vertices[] = {
	-0.5f, -0.5f, 0.0f,	//left
	 0.5f, -0.5f, 0.0f,	//right
	 0.0f,  0.5f, 0.0f,	//top
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//Bind vertex array object then bind and set vertex buffer(s), and then configure vertex attributes
	glBindVertexArray(VAO);

	//copy out vertices array in a buffer for opengl to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//then set our vertex attribute pointers, 
	//this tells opengl how to interpret our data we give it (which is the vertices array)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//note that this is allowed, the call to glVertexAttribPointer registered VBO as
	//the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//you can unbind the VAO afterwards so other VAO calls wont accidentally modify this VAO but this rarely happens
	glBindVertexArray(0);


	while(!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw the object
		shader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}