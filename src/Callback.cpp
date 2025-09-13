#include <glad/glad.h>
#include "Callback.h"
#include "Camera.h"
#include "Game.h"


namespace Callback {

	const int SCREEN_WIDTH = 1920; 
	const int SCREEN_HEIGHT = 1080; 

	static bool firstMouse = true; 
	static float lastX = SCREEN_WIDTH / 2.0f; 
	static float lastY = SCREEN_HEIGHT / 2.0f; 

	void Callback::FrameBufferSize(GLFWwindow* window, int width, int height) {

		glViewport(0, 0, width, height);
	}

	void Callback::Mouse(GLFWwindow* window, double xPosIn, double yPosIn)
	{
		float xpos = static_cast<float>(xPosIn);
		float ypos = static_cast<float>(yPosIn);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;

			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;

		Game::GetCamera().ProcessMouseMovement(xoffset, yoffset); 
	}

	void Callback::Scroll(GLFWwindow* window, double xoffset, double yoffset)
	{
		Game::GetCamera().ProcessMouseScroll(static_cast<float>(yoffset)); 
	}



}

