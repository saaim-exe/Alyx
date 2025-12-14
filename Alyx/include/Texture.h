#pragma once
#include "Util.h"
#include <glad/glad.h>
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace Util; 

namespace TextureProcessing {

	extern const float texCoords[]; 

	GLuint loadTexture(const std::string& path); 
	GLuint loadCubeMap(const std::vector<std::string>& faces);
	
}




