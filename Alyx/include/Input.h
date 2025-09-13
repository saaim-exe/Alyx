#pragma once

namespace Input {

	extern bool _keyPressed[372];
	extern bool _keyDown[372];
	extern bool _keyDownLastFrame[372];

	void Update(); 
	bool keyPressed(unsigned int keycode);
	bool keyDown(unsigned int keycode);
}