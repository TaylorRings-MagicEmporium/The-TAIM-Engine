#pragma once
#include <map>
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
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
	std::string tag;
	std::string name;

public:
	// used for event testing.
	glm::vec3 pos;
	glm::quat rot;
	glm::vec3 scale;

	glm::vec3 defaultPos;
	glm::quat defaultRot;
	glm::vec3 defaultScale;

	// initialisation of the entity class.
	Entity(glm::vec3 StartingPosition, glm::quat StartingRotation,glm::vec3 StartingScale, std::string tag);
	Entity();
	
	// sets the component by it's component type into a map, for easier looking up.
	void SetComponent(Component* com);

	// grabs the component needed by the component type.
	Component* GetComponent(ComponentType t);
	
};

