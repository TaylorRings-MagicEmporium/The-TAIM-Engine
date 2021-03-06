#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// a shader is a specific object that links with openGL and shader files. 
class Shader
{
public:
	unsigned int ID = -1;
	std::string name;
	Shader() {};

	Shader(const char* vertexPath, const char* fragmentPath);

	void Use();

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetVec3(const std::string& name, glm::vec3 value) const;
	void SetVec4(const std::string& name, glm::vec4 value) const;
	void SetMat4(const std::string& name, glm::mat4 value) const;

	bool IsPresent(const std::string& name) const;

};

