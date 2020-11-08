#pragma once
#include "bullet3/btBulletDynamicsCommon.h"
#include "Component.h"

enum class ColliderType { Cube,Sphere };

class Collider : public Component
{
public:
	btCollisionShape* shape;
	ColliderType ColType;
	Collider();

};

