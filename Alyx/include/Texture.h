#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>

namespace Texture {

	extern const float texCoords[]; 

	GLuint loadTexture(const std::string& path); 
	GLuint loadCubeMap(const std::vector<std::string>& faces); 

}




