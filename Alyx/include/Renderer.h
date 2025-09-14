#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>
#include <vector>

namespace Renderer {
	
	extern Shader _cubeShader, _lightShader, _skyBoxShader;
	extern GLuint _cubeVAO, _cubeVBO, _cubeEBO;
	extern GLuint _lightVAO, _lightVBO, _lightEBO; 
	extern GLuint _skyBoxVAO, _skyBoxVBO, _skyBoxEBO; 
	extern glm::vec3 lightPos; 


	void Init(); 
	void DrawCube(); 
	void DrawLight(); 
	void DrawSkybox(); 
	void RenderFrame(); 

}