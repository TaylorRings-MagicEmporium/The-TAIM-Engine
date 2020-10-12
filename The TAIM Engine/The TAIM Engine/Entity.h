#pragma once
#include <map>
#include "Component.h"
#include <glm/glm.hpp>
#include <string>

class Component;
enum class ComponentType;

class Entity
{
private:
	std::map<ComponentType, Component*> ComponentList;

public:
	glm::vec3 pos;
	Entity();
	void SetComponent(Component* com);
	Component* GetComponent(ComponentType t);
	
};

