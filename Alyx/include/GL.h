#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>


namespace GL {

	extern GLFWwindow* _window;

	void Init(int width, int height, std::string title);

	GLFWwindow* GetWindowPointer();
	bool WindowisOpen();
	void SetWindowShouldClose(bool value);
	void SwapBuffersPollEvents();
	void Cleanup();

}