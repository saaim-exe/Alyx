#include "GL.h"

	namespace GL {

	GLFWwindow* _window = nullptr; 
	}


	void GL::Init(int width, int height, std::string title)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (_window == NULL) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(_window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}
	}

	GLFWwindow* GL::GetWindowPointer() {
		return _window; 
	}

	bool GL::WindowisOpen() {
		return !glfwWindowShouldClose(_window); 
	}

	void GL::SetWindowShouldClose(bool value) {
		glfwSetWindowShouldClose(_window, value);
	}

	void GL::SwapBuffersPollEvents()
	{
		glfwSwapBuffers(_window);
		glfwPollEvents(); 
	}

	void GL::Cleanup() {
		glfwTerminate(); 
	}

