#include "Mesh.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>



void Mesh::Load()
{
	glGenVertexArrays(1, &VAO); 
	glGenBuffers(1, &VBO); 
	glGenBuffers(1, &EBO); 

	glBindVertexArray(VAO); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); 
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW); 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW); 
	
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0); 

}

void Mesh::Draw(Shader& shader)
{

	size_t diffuseNr = 1; 
	size_t specularNr = 1; 

	for (size_t i = 0; i < m_textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i); 
		
		std::string number; 
		std::string name = m_textures[i].type; 

		if (name != "texture_diffuse" && name != "texture_specular") continue;

		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseNr++); 
		}
		else if (name == "texture_specular")
		{
			number = std::to_string(specularNr++); 
		}

		shader.setInt(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, m_textures[i].id); 
	}

	glActiveTexture(GL_TEXTURE0);


	glBindVertexArray(VAO); 
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0); 
	glBindVertexArray(0); 

}
