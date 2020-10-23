#pragma once
#include "bullet3/btBulletDynamicsCommon.h"
#include "Component.h"

enum class ShapeTypes { Cube };

class Collider : public Component
{
public:
	Collider(btVector3 AxisExtents);
	btBoxShape* shape;
};

