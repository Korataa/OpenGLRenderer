#include "../include/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec3 position, const glm::vec3 worldUp) : position(position), worldUp(worldUp)
{
	yaw = -90.0f;
	pitch = 0.0f;
	lastx = 0.0f;
	lasty = 0.0f;
	mouseSens = 0.05f;
	movementSpeed = 5.0f;
	zoom = 45.0f;
	//updates camera values
	update();
}

Camera::Camera(const float x, const float y, const float z, const glm::vec3 worldUp) : worldUp(worldUp)
{
	yaw = -90.0f;
	pitch = 0;
	lastx = 0.0f;
	lasty = 0.0f;
	mouseSens = 0.05f;
	movementSpeed = 5.0f;
	zoom = 45.0f;
	position = glm::vec3(x, y, z);
	//updates camera values
	update();
}

void Camera::update()
{
	glm::vec3 frontVec;
	frontVec.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	frontVec.y = sin(glm::radians(pitch));
	frontVec.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(frontVec);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));

	view = glm::lookAt(position, position + front, up);
}

void Camera::handleMouseInput(float xpos, float ypos, GLboolean pitchConstrain)
{
	float offsetx = xpos - lastx;
	float offsety = lasty - ypos;	//reversed because the y axis is the other way around

	lastx = xpos;
	lasty = ypos;

	offsetx *= mouseSens;
	offsety *= mouseSens;

	yaw += offsetx;
	pitch += offsety;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitchConstrain)
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

}

void Camera::handleKeyboardInput(CameraMovement direction, float deltaTime)
{
	float velocity = deltaTime * movementSpeed;
	switch (direction)
	{
	case FORWARD:
		position += front * velocity;
		break;
	case BACKWARD:
		position -= front * velocity;
		break;
	case LEFT:
		position -= right * velocity;
		break;
	case RIGHT:
		position += right * velocity;
		break;
	}
}