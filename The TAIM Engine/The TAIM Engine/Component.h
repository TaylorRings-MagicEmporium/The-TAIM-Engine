#pragma once
#include "Entity.h"

class Entity;

enum class ComponentType { MeshRenderer, Rigidbody };


// the component class is used to marely state which objects are components.
// this allows for quick access form the entity if the componentType was known.
class Component
{

public:
	ComponentType type;
};

