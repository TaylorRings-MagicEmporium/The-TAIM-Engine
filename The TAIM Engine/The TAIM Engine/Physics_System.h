#pragma once
#include "EventQueue.h"
#include "bullet3/btBulletDynamicsCommon.h"
#include "Rigidbody.h"
#include "Collider.h"
#include <vector>
#include "Communication_Layer.h"
#include "Bullet_Debug_Drawer.h"
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

	Bullet_Debug_Drawer BDD = Bullet_Debug_Drawer();

	//EVENT HANDLERS
	void MoveForward(Event* e);
	void MoveLeft(Event* e);
	void MoveBackward(Event* e);
	void MoveRight(Event* e);
	void FJump(Event* e);
public:
	Communication_Layer* CL;
	Physics_System(int ComponentSize);

	void Setup();

	void Update(EventQueue* EQ);

	Component* CreateRigidbody(glm::vec3 offset, float RBmass);
	Component* CreateCollider(glm::vec3 axisExtents);

	~Physics_System();
};

