#pragma once
#include <GLFW/glfw3.h>


namespace Callback {	

	void FrameBufferSize(GLFWwindow* window, int width, int height); 
	void Mouse(GLFWwindow* window, double xPosIn, double yPosIn); 
	void Scroll(GLFWwindow* window, double xoffset, double yoffset); 

}