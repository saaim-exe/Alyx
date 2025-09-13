#pragma once
#include <glad/glad.h>
#include <string>

namespace Texture {

	extern const float texCoords[]; 

	GLuint loadTexture(const std::string& path); 


}




