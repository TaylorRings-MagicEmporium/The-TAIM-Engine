#pragma once
#include "bullet3/btBulletDynamicsCommon.h"
#include "Collider.h"
#include "Component.h"
class Rigidbody : public Component
{
public:
	float mass = 0.0f;
	btVector3 LockAxis = btVector3(1, 1, 1);
	bool IsDynamic;
	btVector3 localInertia = btVector3(0, 0, 0);
	btDefaultMotionState* motionState;
	btRigidBody* body;
	Collider* collider;
	btTransform RBTransform;
	btVector3 offset;
	Rigidbody(btVector3 offset, float RBmass);

	void Setup();
	void ConstrictRotation(bool lockX,bool lockY, bool lockZ);
};

