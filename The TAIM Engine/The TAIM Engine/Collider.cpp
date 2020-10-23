#include "Collider.h"

Collider::Collider(btVector3 AxisExtents)
{
	type = ComponentType::Collider;
	shape = new btBoxShape(AxisExtents);
}
