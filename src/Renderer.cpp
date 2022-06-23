#include "../include/Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include "../include/Light.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double posX, double posY);
bool mouseHasMoved = false;
float lastX;
float lastY;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const std::string vShaderPath = "resources/shaders/shader.vert";
const std::string fShaderPath = "resources/shaders/shader.frag";

const glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 7.0f);
const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

std::vector<GLfloat> vertices = 
{
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};



Light light(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f));
Shader lightingShader;

unsigned int lightVAO;

Renderer::Renderer() : camera(cameraPosition, worldUp)
{
	isRunning = false;
	VBO = NULL;
	VAO = NULL;
	window = NULL;
	projection = glm::mat4(1.0);

	deltaTime = 0;
	lastFrame = 0;
}

bool Renderer::initOpenGL()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My Renderer", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	shader.loadShaders("resources/shaders/shader.vert", "resources/shaders/shader.frag");
	lightingShader.loadShaders("resources/shaders/shader.vert", "resources/shaders/lighting.frag");

	light.vertices = vertices;

	objects.push_back(OpenGLObject(glm::vec3(0.0f, 3.0f, 0.60f), vertices));
	objects.push_back(OpenGLObject(glm::vec3(2.0f, 0.0f, -3.0f), vertices));
	objects.push_back(OpenGLObject(glm::vec3(0.0f, -2.0f, 0.0f), vertices));

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	//Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//lighr cube stuff
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	
	shader.use();
	shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	shader.setVec3("lightPos", light.position);

	return true;
}

bool Renderer::startRendering()
{
	if (isRunning)
	{
		//we return because we dont want to run the renderer 2 times
		return false;
	}
	isRunning = true;
	//Main loop, the app "lives" inside here
	while (isRunning)
	{
		//Blah blah main loop stuff
		if (glfwWindowShouldClose(window))
		{
			isRunning = false;
			//renderer closed successfully so return true
			return true;
		}

		//Delta time stuff
		float time = glfwGetTime();
		deltaTime = time - lastFrame;
		lastFrame = time;

		// input
		// -----
		processInput(window);

		//update
		camera.update();

		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

		// activate shader
		shader.use();

		// create transformations // make sure to initialize matrix to identity matrix first
		projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		shader.setMat4("projection", projection);
		shader.setMat4("view", camera.view);

		//lighting
		shader.setVec3("viewPos", camera.position);

		// render box
		glBindVertexArray(VAO);
		for (int i = 0; i < objects.size(); ++i)
		{
			shader.setMat4("model", objects[i].model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lightingShader.use();

		glm::mat4 lightModel = glm::mat4(1.0);
		lightModel = glm::translate(lightModel, light.position);
		lightModel = glm::scale(lightModel, glm::vec3(0.2f));
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", camera.view);
		lightingShader.setMat4("model", lightModel);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//deallocate resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return true;

}

void Renderer::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	//CAMERA
	//Keyboard movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.handleKeyboardInput(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.handleKeyboardInput(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.handleKeyboardInput(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.handleKeyboardInput(RIGHT, deltaTime);

	//Mouse movement
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	camera.handleMouseInput(xpos, ypos);
}

void Renderer::destroy()
{
	//deallocate resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double posX, double posY)
{
	float x = (float)posX;
	float y = (float)posY;

	if (!mouseHasMoved)
	{
		//start tracking mouse
		lastX = x;
		lastY = y;
		mouseHasMoved = true;
	}

	float offsetX = x - lastX;
	float offsetY = lastY - y;

	lastX = x;
	lastY = y;

	//camera.handleMouseInput(offsetX, offsetY);
}