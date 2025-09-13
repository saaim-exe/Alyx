#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Camera::ProcessKeyboard(CAMERA_MOVEMENT direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	float speedBoost = 0.01f;

	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
	if (direction == DOWN)
		Position -= Up * velocity;
	if (direction == UP)
		Position += Up * velocity;
	if (direction == BOOST)
		Position += (Front * speedBoost);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;


	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch)
	{
		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}
		if (Pitch < -89.0f)
		{
			Pitch = -89.0f;
		}
	}


	updateCameraVectors();

}

void Camera::ProcessMouseScroll(float yoffset) {

	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
	{
		Zoom = 1.0f;
	}
	if (Zoom > 45.0f)
	{
		Zoom = 45.0f;
	}

}

void Camera::updateCameraVectors()
{

	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

	Front = glm::normalize(front);
	Right = glm::normalize(glm::cross(Front, WorldUp));
	Up = glm::normalize(glm::cross(Right, Front));

}


glm::mat4 Camera::GetModelMatrix()
{
	return _model;
}
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}
glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspective(glm::radians(Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
}
