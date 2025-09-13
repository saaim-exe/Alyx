#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

struct Shader {

	int _ID = 0;
	std::unordered_map<std::string, int> _uniformLocations; 

	int checkErrors(unsigned int shader, std::string type);
	void Load(const std::string& vertexPath, const std::string& fragmentPath); 
	void Bind(); 

	// utility functions 
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, const glm::vec2& value) const;
	void setVec2(const std::string& name, float x, float y) const;
	void setVec3(const std::string& name, const glm::vec3& value) const; 
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const; 
	void setMat4(const std::string& name, const glm::mat4& mat) const;

};