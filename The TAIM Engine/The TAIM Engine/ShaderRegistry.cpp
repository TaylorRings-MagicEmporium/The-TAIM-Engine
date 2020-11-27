#include "ShaderRegistry.h"
#include <iostream>

ShaderRegistry::ShaderRegistry() {

}

ShaderRegistry::~ShaderRegistry() {

}
// makes sure only one shader program is made for each type.
Shader* ShaderRegistry::CreateShader(std::string name, const char* vertexPath, const char* fragmentPath) {
	shaderList[name] = Shader(vertexPath, fragmentPath);
	list.push_back(&shaderList[name]);
	shaderList[name].name = name;
	return &shaderList[name];
}


Shader* ShaderRegistry::GetShader(std::string name) {
	if (shaderList.count(name)) {
		return &shaderList[name];
	}
	else {
		std::cout << "shader called " << name << " does not exist in the registry! setting basic shader" << std::endl;
	}
	return &shaderList["basic"];
}

std::vector<Shader*> ShaderRegistry::GetAllShaders() {
	return list;
}
