#pragma once
#include "EventQueue.h"
#include "bullet3/btBulletDynamicsCommon.h"
#include "Rigidbody.h"
#include "Collider.h"
#include <vector>
#include "Communication_Layer.h"
class Physics_System
{
private:
	btDiscreteDynamicsWorld* dynamicWorld;
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btCollisionDispatcher* dispacher;

	std::vector<Rigidbody> ListOfRigidbodies;
	std::vector<Collider> ListOfColliders;
public:
	Physics_System(int ComponentSize);

	void Setup();

	void Update(EventQueue* EQ, Communication_Layer* CL);

	Component* CreateRigidbody(glm::vec3 offset, float RBmass);
	Component* CreateCollider(glm::vec3 axisExtents);

	~Physics_System();
};

