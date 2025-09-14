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


	Shader _cubeShader, _lightShader, _skyBoxShader;
	GLuint _cubeVAO = 0, _cubeVBO = 0, _cubeEBO = 0;
	GLuint _lightVAO = 0, _lightVBO = 0, _lightEBO = 0; 
	GLuint _skyBoxVAO = 0, _skyBoxVBO = 0, _skyBoxEBO = 0;

	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);


	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(2.0f, 5.0f,-15.0f),
		glm::vec3(-1.5f,-2.2f,-2.5f),
		glm::vec3(-3.8f,-2.0f,-12.3f),
		glm::vec3(2.4f,-0.4f,-3.5f),
		glm::vec3(-1.7f, 3.0f,-7.5f),
		glm::vec3(1.3f,-2.0f,-2.5f),
		glm::vec3(1.5f, 2.0f,-2.5f),
		glm::vec3(1.5f, 0.2f,-1.5f),
		glm::vec3(-1.3f, 1.0f,-1.5f)
	};


	

	void Init() {
		_cubeShader.Load("cube.vert", "cube.frag");
		_lightShader.Load("light.vert", "light.frag"); 
		_skyBoxShader.Load("skybox.vert", "skybox.frag");
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

	void DrawSkybox() {

		std::vector<float> vertices{
			// positions          
		   -1.0f,  1.0f, -1.0f,
		   -1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
		   -1.0f,  1.0f, -1.0f,

		   -1.0f, -1.0f,  1.0f,
		   -1.0f, -1.0f, -1.0f,
		   -1.0f,  1.0f, -1.0f,
		   -1.0f,  1.0f, -1.0f,
		   -1.0f,  1.0f,  1.0f,
		   -1.0f, -1.0f,  1.0f,

			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,

		   -1.0f, -1.0f,  1.0f,
		   -1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f, -1.0f,  1.0f,
		   -1.0f, -1.0f,  1.0f,

		   -1.0f,  1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
		   -1.0f,  1.0f,  1.0f,
		   -1.0f,  1.0f, -1.0f,

		   -1.0f, -1.0f, -1.0f,
		   -1.0f, -1.0f,  1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
		   -1.0f, -1.0f,  1.0f,
			1.0f, -1.0f,  1.0f
		};

		if (_skyBoxVAO == 0)
		{
			glGenVertexArrays(1, &_skyBoxVAO);
			glBindVertexArray(_skyBoxVAO);

			glGenBuffers(1, &_skyBoxVBO);
			glBindBuffer(GL_ARRAY_BUFFER, _skyBoxVBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

			/*glGenBuffers(1, &_skyBoxEBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _skyBoxEBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);*/

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

		}

		glBindVertexArray(_skyBoxVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36); 
			
	}







	void RenderFrame() {

		glClearColor(0.25, 0.25, 0.25, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		_cubeShader.Bind();
		_cubeShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f); 
		_cubeShader.setVec3("viewPos", Game::GetCameraPosition()); 
		_cubeShader.setMat4("projection", Game::GetCamera().GetProjectionMatrix());
		_cubeShader.setMat4("view", Game::GetCamera().GetViewMatrix());

		// material example (1. material components 2. light components)

		_cubeShader.setInt("material.diffuse", 0); 
		_cubeShader.setInt("material.specular", 1); 
		_cubeShader.setFloat("material.shininess", 32.0f); 

		_cubeShader.setVec3("light.position", lightPos); 
		_cubeShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f); 
		_cubeShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		_cubeShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f); 

		_cubeShader.setFloat("light.constant", 1.0f);
		_cubeShader.setFloat("light.linear",0.09f);
		_cubeShader.setFloat("light.quadratic", 0.032f);



		//cube.position = glm::vec3(0.0f, 0.0f, 0.0f);
		//cube.scale = glm::vec3(1);
		

		for (int i = 0; i < 10; ++i)
		{

			cube.position.x = cubePositions[i].x;
			cube.position.y = cubePositions[i].y; 
			cube.position.z = cubePositions[i].z; 
			cube.rotation.x = cubePositions[i].x;
			cube.rotation.y = cubePositions[i].y;
			cube.rotation.z = cubePositions[i].z;


			glm::mat3 normal = glm::inverseTranspose(glm::mat3(cube.to_mat4()));
			_cubeShader.setMat3("normal", normal);
			_cubeShader.setMat4("model", cube.to_mat4());
			DrawCube();
		}
		

		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Game::GetDiffuseTex());

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Game::GetSpecularTex()); 


		_lightShader.Bind();
		_lightShader.setMat4("projection", Game::GetCamera().GetProjectionMatrix());
		_lightShader.setMat4("view", Game::GetCamera().GetViewMatrix()); 
		light.position = glm::vec3(1.2f, 1.0f, 2.0f);
		light.scale = glm::vec3(0.2); 
		_lightShader.setMat4("model", light.to_mat4()); 
		
		DrawLight(); 

		// skybox 

		glDepthFunc(GL_LEQUAL); 
		glDepthMask(GL_FALSE);
		_skyBoxShader.Bind();
		_skyBoxShader.setInt("skybox", 0); 
		_skyBoxShader.setMat4("projection", Game::GetCamera().GetProjectionMatrix());

		glm::mat4 view = glm::mat4(glm::mat3(Game::GetCamera().GetViewMatrix()));

		_skyBoxShader.setMat4("view", view);
		glActiveTexture(0); 
		glBindTexture(GL_TEXTURE_CUBE_MAP, Game::GetSkyboxTex());
		DrawSkybox();
		glDepthMask(GL_TRUE);
		glDepthMask(GL_LESS); 

		
		if (Input::keyPressed(GLFW_KEY_H))
		{
			_cubeShader.Load("cube.vert", "cube.frag");
			_lightShader.Load("light.vert", "light.frag");
		}



	}

}
