#pragma once
#include "Collider.h"
#include "bullet3/btBulletDynamicsCommon.h"
class CubeCollider : public Collider
{
protected:
public:
	CubeCollider(btVector3 AxisExtents);
};

