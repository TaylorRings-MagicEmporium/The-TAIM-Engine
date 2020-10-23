#include "Rigidbody.h"
#include <iostream>
Rigidbody::Rigidbody(btVector3 offset, float RBmass)
{
	type = ComponentType::Rigidbody;
	this->mass = RBmass;
	this->offset = offset;
	//RBTransform.setIdentity();
	//RBTransform.setOrigin(btVector3(position.x, position.y, position.z));
}

void Rigidbody::Setup() {

	RBTransform.setIdentity();
	RBTransform.setOrigin(btVector3(GO->pos.x + offset.getX(), GO->pos.y + offset.getY(), GO->pos.z + offset.getZ()));
	RBTransform.setRotation(btQuaternion(GO->rot.w,GO->rot.x, GO->rot.y, GO->rot.z));

	collider = (Collider*)GO->GetComponent(ComponentType::Collider);

	if (collider) {
		//std::cout << "COLLIDER DETECTED" << std::endl;
		IsDynamic = (mass != 0.f);
		if (IsDynamic) {
			collider->shape->calculateLocalInertia(mass, localInertia);
		}

		motionState = new btDefaultMotionState(RBTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, collider->shape, localInertia);
		body = new btRigidBody(rbInfo);
	}
	else {
		//collider->shape = new btEmptyShape();

		std::cout << "WARNING::NO COLLIDER DETECTED! creating empty shape" << std::endl;

		motionState = new btDefaultMotionState(RBTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, new btEmptyShape(), localInertia);
		body = new btRigidBody(rbInfo);
	}
}
