#pragma once
#include "Collider.h"
#include "bullet3-3.0.6/btBulletDynamicsCommon.h"
class SphereCollider : public Collider
{
public:
	SphereCollider(float radius);
};

