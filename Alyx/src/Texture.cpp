#define STB_IMAGE_IMPLEMENTATION
#include <stbi/stb_image.h>
#include "Texture.h"
#include <iostream>

namespace Texture {
	
	const float Texture::texCoords[] = {
	0.0f, 0.0f, // bottom left
	1.0f, 0.0f, // bottom right 
	0.0f, 1.0f, // top left 
	1.0f, 1.0f // top right
	};

	GLuint loadTexture(const std::string& path)
	{
		GLuint texture;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// wrapping +filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;

		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);


		if (data)
		{
			GLenum format;
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{

			std::cout << "Failed to load texture" << std::endl;

		}

		stbi_image_free(data);

		return texture;
	}

}