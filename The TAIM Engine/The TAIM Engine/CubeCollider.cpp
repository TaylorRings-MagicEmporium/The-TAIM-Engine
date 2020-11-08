#include "CubeCollider.h"

CubeCollider::CubeCollider(btVector3 AxisExtents) {
	//type = ComponentType::Collider;
	ColType = ColliderType::Cube;
	shape = new btBoxShape(AxisExtents);
}