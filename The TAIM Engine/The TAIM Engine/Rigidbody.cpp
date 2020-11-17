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
	RBTransform.setRotation(btQuaternion(GO->rot.x, GO->rot.y, GO->rot.z, GO->rot.w));

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

		//body->setAngularFactor(btVector3(0, 1, 0));
		body->setAngularFactor(LockAxis);
	}
	else {
		//collider->shape = new btEmptyShape();

		std::cout << "WARNING::NO COLLIDER DETECTED! creating empty shape" << std::endl;

		motionState = new btDefaultMotionState(RBTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, new btEmptyShape(), localInertia);
		body = new btRigidBody(rbInfo);
	}
}

void Rigidbody::ConstrictRotation(bool lockX, bool lockY, bool lockZ) {
	//btVector3 t = btVector3(1,1,1);
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
