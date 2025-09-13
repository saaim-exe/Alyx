#include "Shader.h"
#include "Util.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

int Shader::checkErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "Shader compilation error: " << type << "\n" << infoLog << "\n";
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "Shader linking error: " << type << "\n" << infoLog << "\n";
		}
	}
	return success;

}

void Shader::Load(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexSource = Util::ReadTextFromFile("res/shaders/" + vertexPath);
	std::string fragmentSource = Util::ReadTextFromFile("res/shaders/" + fragmentPath);
	const char* vShaderCode = vertexSource.c_str();
	const char* fShaderCode = fragmentSource.c_str();
	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkErrors(vertex, "VERTEX");
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkErrors(fragment, "FRAGMENT"); 
	int tempID = glCreateProgram();
	glAttachShader(tempID, vertex);
	glAttachShader(tempID, fragment);
	glLinkProgram(tempID);
	if (checkErrors(tempID, "PROGRAM")) {
		_uniformLocations.clear();
		_ID = tempID;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Bind() {
	
	if (_ID != 0)
	{
		glUseProgram(_ID);

	} 
}

void Shader::setBool(const std::string& name, bool value)const
{
	glUniform1i(glGetUniformLocation(_ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value)const
{
	glUniform1i(glGetUniformLocation(_ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value)const
{
	glUniform1f(glGetUniformLocation(_ID, name.c_str()), value);
}
void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(_ID, name.c_str()), x, y);
}
void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(_ID, name.c_str()), x, y, z);
}
void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


