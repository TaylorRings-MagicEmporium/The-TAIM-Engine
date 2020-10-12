#pragma once

#include "Shader.h"
#include <map>
#include <vector>
#include <string>
class ShaderRegistry
{
protected:
	std::map<std::string, Shader> shaderList;
	std::vector<Shader*> list;
public:

	ShaderRegistry();
	~ShaderRegistry();

	Shader* CreateShader(std::string name, const char* vertexPath, const char* fragmentPath);

	Shader* GetShader(std::string name);

	std::vector<Shader*> GetAllShaders();

	//void 


};

