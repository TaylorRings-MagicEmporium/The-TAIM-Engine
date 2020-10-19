#pragma once
#include "EventQueue.h"
#include "bullet3/btBulletDynamicsCommon.h"
#include <vector>
class Physics_System
{
private:
	btDiscreteDynamicsWorld* dynamicWorld;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btCollisionDispatcher* dispacher;
public:
	Physics_System(int ComponentSize);

	void Setup();

	void Update(EventQueue* EQ);

	~Physics_System();
};

