#include "Game.h"
#include "GL.h"
#include "Input.h"
#include "Texture.h"
#include "TexturePaths.h"
#include "Camera.h"
#include <unordered_map>

namespace {

	Camera camera; 
	glm::mat4 view; 
	float deltaTime = 0.0f; 
	float lastFrame = 0.0f; 

	GLuint _texID = 0; 
	GLuint _diffuseTex = 0; 
	GLuint _specularTex = 0; 
	GLuint _skyBoxTex = 0; 

}

namespace Game {

	void Init() {
		camera.Position = glm::vec3(3.75f, 5.0f, 10.3f);

		// std::unordered_map<std::string, GLuint> textures; 

		_texID = Texture::loadTexture("res/textures/" + TexturePaths::metalbox);
		_diffuseTex = Texture::loadTexture("res/textures/" + TexturePaths::metalbox_diffuse); 
		_specularTex = Texture::loadTexture("res/textures/" + TexturePaths::metalbox_specular); 

		// skybox /cubemap 

		std::vector<std::string> faces;

		for (const auto& f : TexturePaths::cubeMapFaces)
		{
			faces.push_back("res/textures/skyboxes/Dusk/" + f); 
		}

		// load!! 
		_skyBoxTex = Texture::loadCubeMap(faces); 
	}


	void Update() {

		static bool polygonMode = false;
		static bool keyPressed = false;


		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		if (Input::keyDown(GLFW_KEY_ESCAPE))
		{
			GL::SetWindowShouldClose(true);
		}

		//wireframe mode 

		if (Input::keyDown(GLFW_KEY_T))
		{
			if (!keyPressed)
			{
				polygonMode = !polygonMode;
				if (polygonMode)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}
				else
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				}
				keyPressed = true;
			}
		}
		else
		{
			keyPressed = false;
		}


		if (Input::keyDown(GLFW_KEY_A))
		{
			camera.ProcessKeyboard(LEFT, deltaTime);
		}
		if (Input::keyDown(GLFW_KEY_D))
		{
			camera.ProcessKeyboard(RIGHT, deltaTime);
		}
		if (Input::keyDown(GLFW_KEY_W))
		{
			camera.ProcessKeyboard(FORWARD, deltaTime);
		}
		if (Input::keyDown(GLFW_KEY_S))
		{
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		}
		if (Input::keyDown(GLFW_KEY_SPACE))
		{
			camera.ProcessKeyboard(UP, deltaTime);
		}
		if (Input::keyDown(GLFW_KEY_LEFT_CONTROL))
		{
			camera.ProcessKeyboard(DOWN, deltaTime);
		}
		if (Input::keyDown(GLFW_KEY_LEFT_SHIFT) && !Input::keyDown(GLFW_KEY_S))
		{
			camera.ProcessKeyboard(BOOST, deltaTime);
		}

		view = camera.GetViewMatrix();
	}

	glm::mat4 GetViewMatrix() {
		return view;
	}

	Camera& GetCamera() {
		return camera;
	}

	GLuint GetTextureID() {
		return _texID;
	}

	GLuint GetDiffuseTex()
	{
		return _diffuseTex;
	}
	GLuint GetSpecularTex()
	{
		return _specularTex;
	}

	GLuint GetSkyboxTex()
	{
		return _skyBoxTex; 
	}

	glm::vec3 GetCameraPosition()
	{
		return camera.Position;
	}

}
