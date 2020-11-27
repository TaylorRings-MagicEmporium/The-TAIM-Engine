#include "Rigidbody.h"
#include <iostream>
Rigidbody::Rigidbody(btVector3 offset, float RBmass)
{
	type = ComponentType::Rigidbody;
	this->mass = RBmass;
	this->offset = offset;
}

void Rigidbody::Setup() {

	RBTransform.setIdentity();
	RBTransform.setOrigin(btVector3(GO->transform.position.x + offset.getX(), GO->transform.position.y + offset.getY(), GO->transform.position.z + offset.getZ()));
	RBTransform.setRotation(btQuaternion(GO->transform.Rotation.x, GO->transform.Rotation.y, GO->transform.Rotation.z, GO->transform.Rotation.w));

	collider = (Collider*)GO->GetComponent(ComponentType::Collider);

	if (collider) { // if collider exist, then use that collider, if not, use an empty shape.
		IsDynamic = (mass != 0.f);
		if (IsDynamic) {
			collider->shape->calculateLocalInertia(mass, localInertia);
		}

		motionState = new btDefaultMotionState(RBTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, collider->shape, localInertia);
		body = new btRigidBody(rbInfo);

		body->setAngularFactor(LockAxis);
	}
	else {

		std::cout << "WARNING::NO COLLIDER DETECTED! creating empty shape" << std::endl;

		motionState = new btDefaultMotionState(RBTransform); // motion states are simple bullet packets
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, new btEmptyShape(), localInertia);
		body = new btRigidBody(rbInfo);
	}
}

void Rigidbody::ConstrictRotation(bool lockX, bool lockY, bool lockZ) {
	if (lockX) {
		LockAxis.setX(0);
	}
	if (lockY) {
		LockAxis.setY(0);
	}
	if (lockZ) {
		LockAxis.setZ(0);
	}

}
