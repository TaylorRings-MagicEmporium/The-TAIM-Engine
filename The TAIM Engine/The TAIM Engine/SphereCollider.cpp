#include "SphereCollider.h"


SphereCollider::SphereCollider(float radius) {
	ColType = ColliderType::Sphere;
	shape = new btSphereShape(radius);
}