#pragma once
#include <bullet3-3.0.6/btBulletDynamicsCommon.h>
#include "BulletContactResultCallback.h"
#include <Bullet3-3.0.6/BulletCollision/NarrowPhaseCollision/btRaycastCallback.h>
#include "Rigidbody.h"
//#include "Collider.h"
#include <vector>
#include "Communication_Layer.h"
#include "Bullet_Debug_Drawer.h"
#include "CubeCollider.h"
#include "SphereCollider.h"
#include "SubSystem.h"

#include "Profiling_System.h"

// the Physics_System is responsible for all physics-related inquires from itself or from events.
// it stores rigidbodies and colliders.
class Physics_System : public SubSystem
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
	void TestGunShot(Event* e);
	void HideRigidbodyComponent(Event* e);


public:
	Physics_System();
	~Physics_System();

	void Startup();
	void ShutDown();
	void Update();
	void SetComponentSize(int size);
	void ResetSystem();
	void SyncComponentsToSystem();

	void ColliderCallBack();

	Component* CreateRigidbody(glm::vec3 offset, float RBmass);
	Component* CreateCubeCollider(glm::vec3 axisExtents);
	Component* CreateSphereCollider(float radius);

	// sets the boolean to hide the rigidbody of that entity.
	void ToggleHidingComponent(ComponentType c, Entity* e);
	
	// hides the rigidbody of that entity.
	void HideAdjust(ComponentType c, Entity* e);
	void SetupRigidbodies();
};

