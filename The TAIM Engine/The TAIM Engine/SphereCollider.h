#pragma once
#include "Collider.h"
#include "bullet3-3.0.6/btBulletDynamicsCommon.h"

// CubeCollder is a child of Collider that specifies a 3D cube.
class SphereCollider : public Collider
{
public:
	SphereCollider(float radius);
};

