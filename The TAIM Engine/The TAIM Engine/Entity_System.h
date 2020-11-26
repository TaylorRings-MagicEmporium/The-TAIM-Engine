#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "Entity.h"
#include "SubSystem.h"

//class SubSystem;
class Entity_System : public SubSystem
{
private:
	std::vector<Entity*> ALL_ENTITIES;
	std::map<std::string, std::vector<Entity*>> Tag_System;

	void GunshotInfo(Event* e);
public:

	Entity_System();
	void Update();
	void ResetSystem();
	Entity* CreateEntity(glm::vec3 Position, glm::quat Rotation,glm::vec3 Scale, std::string tag, std::string FileTag, std::string name);
	std::vector<Entity*> GetEntitiesWithTag(std::string tag);
	Entity* GetEntityWithName(std::string name);
	void CloseEntitySystem();
};

