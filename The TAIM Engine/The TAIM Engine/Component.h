#pragma once
#include "Entity.h"

class Entity;

enum class ComponentType { MeshRenderer, Rigidbody };

class Component
{

public:
	ComponentType type;
};

