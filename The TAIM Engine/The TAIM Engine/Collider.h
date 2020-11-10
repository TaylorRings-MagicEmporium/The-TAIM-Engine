#pragma once
#include "bullet3-3.0.6/btBulletDynamicsCommon.h"
#include "Component.h"

enum class ColliderType { Cube,Sphere };

class Collider : public Component
{
public:
	btCollisionShape* shape;
	ColliderType ColType;
	Collider();

};

