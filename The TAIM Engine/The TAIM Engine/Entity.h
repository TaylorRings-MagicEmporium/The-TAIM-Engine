#pragma once
#include <map>
#include "Component.h"
#include "Transform.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>

class Component;
enum class ComponentType; // circular dependency

// An entity is a container that holds components related to it.
// this allows systems to grab the component needed to use it.
class Entity
{
private:
	// holds the components related to this entity instance.
	std::map<ComponentType, Component*> ComponentList;

	//std::string name;
	std::string Tag;
	std::string FileTag;
	std::string name;
public:
	// used for event testing.
	Transform transform;

	bool hideEntity = false;

	// initialisation of the entity class.
	Entity(glm::vec3 StartingPosition, glm::quat StartingRotation,glm::vec3 StartingScale, std::string tag, std::string FileTag, std::string name);
	Entity();
	
	// sets the component by it's component type into a map, for easier looking up.
	void SetComponent(Component* com);

	// grabs the component needed by the component type.
	Component* GetComponent(ComponentType t);

	std::string GetTag() { return Tag; };
	std::string GetFileTag() { return FileTag; };
	std::string GetName() { return name; };
	
};

