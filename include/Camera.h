#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum CameraMovement
{
	FORWARD, BACKWARD, LEFT, RIGHT
};

class Camera
{
public:
	//Probably going to leave these public for simplicity
	glm::mat4 view;			//translate to view-coords

	glm::vec3 position;
	//all of these vectors basically form an x, y, and z axis where the cameras position is at (0, 0, 0)
	glm::vec3 front;	//z axis, might be pointing at camera
	glm::vec3 right;	//x axis
	glm::vec3 up;		//y axis
	glm::vec3 worldUp;	//simply the direction of up in the world (probably will be (0, 1.0f, 0))

	//euler angles
	float yaw;		//up and down rotation
	float pitch;	//left and right rotation

	float movementSpeed;
	float mouseSens;
	float zoom;

	Camera(const glm::vec3 position, const glm::vec3 worldUp);
	Camera(const float x, const float y, const float z, const glm::vec3 worldUp);

	//probably called every frame
	//calc vectors and probably the view and projection matrix
	void update();

	void handleKeyboardInput(CameraMovement direction, float deltaTime);
	void handleMouseInput(float xpos, float ypos, GLboolean pitchConstrain = true);

private:
	//last mouse coordinates
	float lastx, lasty;

};