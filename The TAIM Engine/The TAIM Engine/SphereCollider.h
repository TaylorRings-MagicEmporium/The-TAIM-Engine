#pragma once
#include "Collider.h"
#include "bullet3/btBulletDynamicsCommon.h"
class SphereCollider : public Collider
{
public:
	SphereCollider(float radius);
};

