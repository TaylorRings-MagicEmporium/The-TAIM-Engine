#include "SphereCollider.h"


SphereCollider::SphereCollider(float radius) {
	//type = ComponentType::Collider;
	ColType = ColliderType::Sphere;
	shape = new btSphereShape(radius);
}