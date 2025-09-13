#ifndef CAMERA_H
#define CAMERA_H 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

enum CAMERA_MOVEMENT {

	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	DOWN,
	UP,
	BOOST
};

// default cam values 

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 5.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


struct Camera {

	// res
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

	// model , view, projection 
	glm::mat4 _model;
	glm::mat4 _view;
	glm::mat4 _projection;

	//camera attribs 
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	// euler angles 

	float Yaw;
	float Pitch;

	//camera options 

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();

	}

	void ProcessKeyboard(CAMERA_MOVEMENT direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset); 

	glm::mat4 GetModelMatrix(); 
	glm::mat4 GetViewMatrix(); 
	glm::mat4 GetProjectionMatrix(); 

	void updateCameraVectors(); 

};


#endif 