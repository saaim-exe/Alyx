#include "Input.h"
#include "GL.h"
#include <GLFW/glfw3.h>

namespace Input {

	bool _keyPressed[372];
	bool _keyDown[372];
	bool _keyDownLastFrame[372];

	void Update() {

		GLFWwindow* window = GL::GetWindowPointer();
		for (int i = 30; i < 350; i++) {
			_keyDown[i] = (glfwGetKey(window, i) == GLFW_PRESS);
			_keyPressed[i] = (_keyDown[i] && !_keyDownLastFrame[i]);
			_keyDownLastFrame[i] = _keyDown[i];
		}

	}

	bool keyPressed(unsigned int keycode)
	{
		return _keyPressed[keycode];
	}

	bool keyDown(unsigned int keycode)
	{
		return _keyDown[keycode];
	}

}

