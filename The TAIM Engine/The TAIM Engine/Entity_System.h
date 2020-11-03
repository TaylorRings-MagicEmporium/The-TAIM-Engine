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
	Entity* CreateEntity(glm::vec3 Position, glm::quat Rotation, std::string tag);
	std::vector<Entity*> GetEntitiesWithTag(std::string tag);
	void CloseEntitySystem();
};
