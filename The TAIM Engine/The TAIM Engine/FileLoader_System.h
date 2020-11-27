#pragma once
#include <glm/glm.hpp>
#include <string>

#include "Entity.h"
#include "ShaderRegistry.h"

#include "ShaderRegistry.h"
#include "Graphics_System.h"
#include "Physics_System.h"
#include "Entity_System.h"
#include "Audio_System.h"
#include "Camera_System.h"
#include "Animation_System.h"
#include "Profiling_System.h"
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
	glm::vec3 scale = glm::vec3(1);
	std::string tag = "undefined";
	std::string FileTag = "undefined";
	std::string name = "undefined";
};


class FileLoader_System
{
	//the file loader system is capable of setting up the majority of the scene.
	//this also include the initial config file with resource paths and multiple entity scripts
	// that describes transform and hierarchies.
private:
	std::string ResourcePATH;
	std::vector<std::string> LevelFiles;
	int fileCount = 0;
public:
	
	Graphics_System* GS;
	Physics_System* PS;
	ShaderRegistry* SR;
	Entity_System* ES;
	Audio_System* AS;
	Camera_System* CS;
	Animation_System* AnS;


	FileLoader_System();
	// function doesn't exist
	void LoadShaders();

	// load entities from a file and puts their components in the respective places.
	void LoadEntities();
	ConfigData LoadConfig();

	//swaps the main file to the specified level in the vector
	void SwapFile(int level);
};

