#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera; 
class Model; 

namespace Game {
	

	void Init(); 
	void Update();
	Camera& GetCamera();
	Model& GetModel(); 
	glm::mat4 GetViewMatrix(); 
	glm::vec3 GetCameraPosition();
	GLuint GetDiffuseTex();
	GLuint GetSpecularTex();
	GLuint GetSkyboxTex();
	GLuint GetTextureID();
	
}