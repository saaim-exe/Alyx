#pragma once
#include "Util.h"
#include "Shader.h"
#include <vector>

using namespace Util;


struct Mesh {

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) : m_vertices(vertices), m_indices(indices), m_textures(textures)
	{
		Load(); 
	}


	unsigned int VAO, VBO, EBO; 

	std::vector<Vertex> m_vertices; 
	std::vector<unsigned int> m_indices; 
	std::vector<Util::Texture> m_textures;

	void Load(); 
	void Draw(Shader& shader); 



};