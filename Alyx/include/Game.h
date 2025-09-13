#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera; 

namespace Game {
	

	void Init(); 
	void Update();
	Camera& GetCamera();
	glm::mat4 GetViewMatrix(); 
	GLuint GetTextureID();
}