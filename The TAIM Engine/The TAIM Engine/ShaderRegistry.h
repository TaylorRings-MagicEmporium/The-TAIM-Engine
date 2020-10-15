#pragma once

#include "Shader.h"
#include <map>
#include <vector>
#include <string>

//the shader registry is a resource manager for shaders. it can be quickly used to get a specific shader,
// create a shader and possibly do all-shader operations (updating the view and proj)
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


};

