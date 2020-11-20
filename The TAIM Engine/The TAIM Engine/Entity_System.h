#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "Entity.h"
class Entity_System
{
private:
	std::vector<Entity*> ALL_ENTITIES;
	std::map<std::string, std::vector<Entity*>> Tag_System;

public:
	Entity_System();
	void Update();
	Entity* CreateEntity(glm::vec3 Position, glm::quat Rotation,glm::vec3 Scale, std::string tag, std::string FileTag);
	std::vector<Entity*> GetEntitiesWithTag(std::string tag);
	void CloseEntitySystem();
};

