#pragma once
#include "Util.h"
#include "Shader.h"
#include <vector>

using namespace Util;


struct Mesh {

	unsigned int VAO, VBO, EBO; 

	std::vector<Vertex> vertices; 
	std::vector<unsigned int> indices; 
	std::vector<Texture> textures; 

	void Load(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures); 
	void Draw(Shader& shader); 

	



};