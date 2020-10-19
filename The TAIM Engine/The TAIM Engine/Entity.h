#pragma once
#include <map>
#include "Component.h"
#include <glm/glm.hpp>
#include <string>

class Component;
enum class ComponentType;

// An entity is a container that holds components related to it.
// this allows systems to grab the component needed to use it.
class Entity
{
private:
	// holds the components related to this entity instance.
	std::map<ComponentType, Component*> ComponentList;

public:
	// used for event testing.
	glm::vec3 pos;
	glm::vec3 PosChange;
	// initialisation of the entity class.
	Entity();
	
	// sets the component by it's component type into a map, for easier looking up.
	void SetComponent(Component* com);

	// grabs the component needed by the component type.
	Component* GetComponent(ComponentType t);
	
};

