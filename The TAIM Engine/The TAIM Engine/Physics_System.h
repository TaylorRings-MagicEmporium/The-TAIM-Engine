#pragma once
#include "EventQueue.h"
#include "bullet3-3.0.6/btBulletDynamicsCommon.h"
#include "Rigidbody.h"
//#include "Collider.h"
#include <vector>
#include "Communication_Layer.h"
#include "Bullet_Debug_Drawer.h"
#include "CubeCollider.h"
#include "SphereCollider.h"
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
	void ResetTransformEv(Event* e);
public:
	Communication_Layer* CL;
	Physics_System(int ComponentSize);

	void Setup();

	void Update(EventQueue* EQ);

	Component* CreateRigidbody(glm::vec3 offset, float RBmass);
	//Component* CreateCollider(glm::vec3 axisExtents);
	Component* CreateCubeCollider(glm::vec3 axisExtents);
	Component* CreateSphereCollider(float radius);
	~Physics_System();
};

