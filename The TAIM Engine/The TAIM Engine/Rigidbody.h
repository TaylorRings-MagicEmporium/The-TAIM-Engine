#pragma once
#include "bullet3/btBulletDynamicsCommon.h"
#include "Collider.h"
#include "Component.h"
class Rigidbody : public Component
{
public:
	float mass = 0.0f;
	bool IsDynamic;
	btVector3 localInertia = btVector3(0, 0, 0);
	btDefaultMotionState* motionState;
	btRigidBody* body;
	Collider* collider;
	btTransform RBTransform;
	btVector3 offset;
	Rigidbody(btVector3 offset, float RBmass);

	void Setup();
};

