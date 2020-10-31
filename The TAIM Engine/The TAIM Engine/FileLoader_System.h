#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Entity.h"
#include "ShaderRegistry.h"

#include "ShaderRegistry.h"
#include "Graphics_System.h"
#include "Physics_System.h"

#include <vector>

struct ConfigData {
	bool FileLoaded = false;
	glm::vec2 ScreenSize;
	std::string WindowName;
	int MaxComponentSize;
};

struct TempTransData {
	glm::vec3 position = glm::vec3(0);
	float degrees = 0.0f;
	glm::vec3 rotateAxis = glm::vec3(1);
};


class FileLoader_System
{
	//the file loader system is capable of setting up the majority of the scene.
	//this also include the initial config file with resource paths and multiple entity scripts
	// that describes transform and hierarchies.
private:
	std::string ResourcePATH;

public:
	Graphics_System* GS;
	Physics_System* PS;
	ShaderRegistry* SR;

	FileLoader_System();
	void LoadShaders();
	void LoadEntities(std::vector<Entity*>& EntityList);
	ConfigData LoadConfig();
};

