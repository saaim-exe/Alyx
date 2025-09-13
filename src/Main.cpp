#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "GL.h"
#include "Util.h"
#include "Shader.h"
#include "Callback.h"  
#include "Game.h"
#include "Input.h"
#include "Camera.h"
#include "Texture.h"
#include "Renderer.h"


const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

int main() {

	GL::Init(SCREEN_WIDTH, SCREEN_HEIGHT, "FINAL"); 
	Game::Init();
	Renderer::Init(); 

	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(GL::GetWindowPointer(), Callback::FrameBufferSize); 
	glfwSetCursorPosCallback(GL::GetWindowPointer(), Callback::Mouse); 
	glfwSetScrollCallback(GL::GetWindowPointer(), Callback::Scroll); 
	glfwSetInputMode(GL::GetWindowPointer(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); 


	while (GL::WindowisOpen())
	{
		Input::Update(); 
		Game::Update(); 
		Renderer::RenderFrame(); 

		GL::SwapBuffersPollEvents(); 
	}


	GL::Cleanup(); 
	return EXIT_SUCCESS; 
}

