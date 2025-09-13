#include "Renderer.h"
#include "Util.h"
#include "Camera.h"
#include "Input.h"
#include "Game.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

using namespace Util; 

namespace {
	Transform cube;
	Transform light;
	Transform normal; 
}



namespace Renderer {


	Shader _cubeShader, _lightShader;
	GLuint _cubeVAO = 0, _cubeVBO = 0, _cubeEBO = 0;
	GLuint _lightVAO = 0, _lightVBO = 0, _lightEBO = 0; 
	glm::vec3 lightPos = glm::vec3(0.0f); 


	

	void Init() {
		_cubeShader.Load("cube.vert", "cube.frag");
		_lightShader.Load("light.vert", "light.frag"); 
	}

	void DrawCube() {

		std::vector<int>  indices = {

			0, 1, 2, 2, 3, 0,
				  // Back
			4, 5, 6, 6, 7, 4,
			   // Left
			8, 9,10,10,11, 8,
			 // Right
			12,13,14,14,15,12,
			// Top
			16,17,18,18,19,16,
			// Bottom
			20,21,22,22,23,20
		};


		if (_cubeVAO == 0)
		{
			std::vector<Vertex> vertices{
				{{-0.5f, -0.5f,  0.5f}, {0,0,1}, {0.0f, 0.0f}}, // 0 bottom-left
				{{ 0.5f, -0.5f,  0.5f}, {0,0,1}, {1.0f, 0.0f}}, // 1 bottom-right
				{{ 0.5f,  0.5f,  0.5f}, {0,0,1}, {1.0f, 1.0f}}, // 2 top-right
				{{-0.5f,  0.5f,  0.5f}, {0,0,1}, {0.0f, 1.0f}}, // 3 top-left

				// Back face
				{{-0.5f, -0.5f, -0.5f}, {0,0,-1}, {1.0f, 0.0f}}, 
				{{ 0.5f, -0.5f, -0.5f}, {0,0,-1}, {0.0f, 0.0f}}, 
				{{ 0.5f,  0.5f, -0.5f}, {0,0,-1}, {0.0f, 1.0f}},
				{{-0.5f,  0.5f, -0.5f}, {0,0,-1}, {1.0f, 1.0f}}, 

				// Left face
				{{-0.5f, -0.5f, -0.5f}, {-1,0,0}, {0.0f, 0.0f}}, 
				{{-0.5f, -0.5f,  0.5f}, {-1,0,0}, {1.0f, 0.0f}}, 
				{{-0.5f,  0.5f,  0.5f}, {-1,0,0}, {1.0f, 1.0f}}, 
				{{-0.5f,  0.5f, -0.5f}, {-1,0,0}, {0.0f, 1.0f}},

				// Right face
				{{ 0.5f, -0.5f, -0.5f}, {1,0,0}, {1.0f, 0.0f}},
				{{ 0.5f, -0.5f,  0.5f}, {1,0,0}, {0.0f, 0.0f}}, 
				{{ 0.5f,  0.5f,  0.5f}, {1,0,0}, {0.0f, 1.0f}}, 
				{{ 0.5f,  0.5f, -0.5f}, {1,0,0}, {1.0f, 1.0f}}, 

				// Top face
				{{-0.5f,  0.5f,  0.5f}, {0,1,0}, {0.0f, 0.0f}}, 
				{{ 0.5f,  0.5f,  0.5f}, {0,1,0}, {1.0f, 0.0f}}, 
				{{ 0.5f,  0.5f, -0.5f}, {0,1,0}, {1.0f, 1.0f}}, 
				{{-0.5f,  0.5f, -0.5f}, {0,1,0}, {0.0f, 1.0f}}, 

				// Bottom face
				{{-0.5f, -0.5f,  0.5f}, {0,-1,0}, {1.0f, 0.0f}}, 
				{{ 0.5f, -0.5f,  0.5f}, {0,-1,0}, {0.0f, 0.0f}}, 
				{{ 0.5f, -0.5f, -0.5f}, {0,-1,0}, {0.0f, 1.0f}}, 
				{{-0.5f, -0.5f, -0.5f}, {0,-1,0}, {1.0f, 1.0f}}, 
			};
			
			glGenVertexArrays(1, &_cubeVAO);
			glBindVertexArray(_cubeVAO);

			glGenBuffers(1, &_cubeVBO);
			glBindBuffer(GL_ARRAY_BUFFER, _cubeVBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

			glGenBuffers(1, &_cubeEBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _cubeEBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

		}

		glBindVertexArray(_cubeVAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	}


	void DrawLight() {

		std::vector<int>  indices = {

		0, 1, 2, 2, 3, 0,
		// Back
		4, 5, 6, 6, 7, 4,
		// Left
		8, 9,10,10,11, 8,
		// Right
		12,13,14,14,15,12,
		// Top
		16,17,18,18,19,16,
		// Bottom
		20,21,22,22,23,20
		};


		std::vector<Vertex> vertices{
				{{-0.5f, -0.5f,  0.5f}, {0,0,1}, {0.0f, 0.0f}}, // 0 bottom-left
				{{ 0.5f, -0.5f,  0.5f}, {0,0,1}, {1.0f, 0.0f}}, // 1 bottom-right
				{{ 0.5f,  0.5f,  0.5f}, {0,0,1}, {1.0f, 1.0f}}, // 2 top-right
				{{-0.5f,  0.5f,  0.5f}, {0,0,1}, {0.0f, 1.0f}}, // 3 top-left

				// Back face
				{{-0.5f, -0.5f, -0.5f}, {0,0,-1}, {1.0f, 0.0f}},
				{{ 0.5f, -0.5f, -0.5f}, {0,0,-1}, {0.0f, 0.0f}},
				{{ 0.5f,  0.5f, -0.5f}, {0,0,-1}, {0.0f, 1.0f}},
				{{-0.5f,  0.5f, -0.5f}, {0,0,-1}, {1.0f, 1.0f}},

				// Left face
				{{-0.5f, -0.5f, -0.5f}, {-1,0,0}, {0.0f, 0.0f}},
				{{-0.5f, -0.5f,  0.5f}, {-1,0,0}, {1.0f, 0.0f}},
				{{-0.5f,  0.5f,  0.5f}, {-1,0,0}, {1.0f, 1.0f}},
				{{-0.5f,  0.5f, -0.5f}, {-1,0,0}, {0.0f, 1.0f}},

				// Right face
				{{ 0.5f, -0.5f, -0.5f}, {1,0,0}, {1.0f, 0.0f}},
				{{ 0.5f, -0.5f,  0.5f}, {1,0,0}, {0.0f, 0.0f}},
				{{ 0.5f,  0.5f,  0.5f}, {1,0,0}, {0.0f, 1.0f}},
				{{ 0.5f,  0.5f, -0.5f}, {1,0,0}, {1.0f, 1.0f}},

				// Top face
				{{-0.5f,  0.5f,  0.5f}, {0,1,0}, {0.0f, 0.0f}},
				{{ 0.5f,  0.5f,  0.5f}, {0,1,0}, {1.0f, 0.0f}},
				{{ 0.5f,  0.5f, -0.5f}, {0,1,0}, {1.0f, 1.0f}},
				{{-0.5f,  0.5f, -0.5f}, {0,1,0}, {0.0f, 1.0f}},

				// Bottom face
				{{-0.5f, -0.5f,  0.5f}, {0,-1,0}, {1.0f, 0.0f}},
				{{ 0.5f, -0.5f,  0.5f}, {0,-1,0}, {0.0f, 0.0f}},
				{{ 0.5f, -0.5f, -0.5f}, {0,-1,0}, {0.0f, 1.0f}},
				{{-0.5f, -0.5f, -0.5f}, {0,-1,0}, {1.0f, 1.0f}},
		};


		if (_lightVAO == 0)
		{
			glGenVertexArrays(1, &_lightVAO);
			glBindVertexArray(_lightVAO);

			glGenBuffers(1, &_lightVBO);
			glBindBuffer(GL_ARRAY_BUFFER, _lightVBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

			glGenBuffers(1, &_lightEBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _lightEBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);


			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}


		glBindVertexArray(_lightVAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}




	void RenderFrame() {

		glClearColor(0.1, 0.1, 0.1, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, Game::GetTextureID());

		_cubeShader.Bind();
		_cubeShader.setInt("texture1", 0); 
		_cubeShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f); 
		_cubeShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f); 
		_cubeShader.setVec3("lightPos", 1.2f, 1.0f, 2.0f);
		_cubeShader.setMat4("projection", Game::GetCamera().GetProjectionMatrix());
		_cubeShader.setMat4("view", Game::GetCamera().GetViewMatrix());

		cube.position = glm::vec3(0.0f, 0.0f, 0.0f);
		cube.scale = glm::vec3(1);
		glm::mat3 normal = glm::inverseTranspose(glm::mat3(cube.to_mat4()));
		_cubeShader.setMat3("normal", normal); 
		_cubeShader.setMat4("model", cube.to_mat4()); 
		
		DrawCube(); 

		_lightShader.Bind();
		_lightShader.setMat4("projection", Game::GetCamera().GetProjectionMatrix());
		_lightShader.setMat4("view", Game::GetCamera().GetViewMatrix()); 
		light.position = glm::vec3(1.2f, 1.0f, 2.0f);
		light.scale = glm::vec3(0.2); 
		_lightShader.setMat4("model", light.to_mat4()); 
		
		DrawLight(); 
		
		if (Input::keyPressed(GLFW_KEY_H))
		{
			_cubeShader.Load("cube.vert", "cube.frag");
			_lightShader.Load("light.vert", "light.frag");
		}



	}

}
