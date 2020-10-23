#include "Physics_System.h"
//#include "bullet3/CommonInterfaces/CommonRigidBodyBase.h"

Physics_System::Physics_System(int ComponentSize)
{
	ListOfRigidbodies.reserve(ComponentSize);
	ListOfColliders.reserve(ComponentSize);
}

void Physics_System::Setup()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispacher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver;

	dynamicWorld = new btDiscreteDynamicsWorld(dispacher, overlappingPairCache, solver, collisionConfiguration);

	dynamicWorld->setGravity(btVector3(0, -10, 0));

	for (int i = 0; i < ListOfRigidbodies.size(); i++) {
		ListOfRigidbodies[i].Setup();
		dynamicWorld->addRigidBody(ListOfRigidbodies[i].body);
	}
}

void Physics_System::Update(EventQueue* EQ, Communication_Layer* CL)
{
	dynamicWorld->stepSimulation(1.0f / 60.0f, 10);

	for (int j = 0; j < ListOfRigidbodies.size(); j++) {
		btTransform trans;
		if (ListOfRigidbodies[j].body && ListOfRigidbodies[j].body->getMotionState()) {
			ListOfRigidbodies[j].body->getMotionState()->getWorldTransform(trans);
			CL->GPWrap(trans, ListOfRigidbodies[j].GO);
		}

		//printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
	}


	//for (int j = dynamicWorld->getNumCollisionObjects() - 1; j >= 0; j--) {
	//	btCollisionObject* obj = dynamicWorld->getCollisionObjectArray()[j];
	//	btRigidBody* body = btRigidBody::upcast(obj);
	//	btTransform trans;
	//	if (body && body->getMotionState()) {
	//		body->getMotionState()->getWorldTransform(trans);
	//	}
	//	else {
	//		trans = obj->getWorldTransform();
	//	}
	//	//
	//	
	//}
}

Physics_System::~Physics_System()
{
	for (int i = dynamicWorld->getNumCollisionObjects() - 1; i >= 0; i--) {
		btCollisionObject* obj = dynamicWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState()) {
			delete body->getMotionState();
		}
		dynamicWorld->removeCollisionObject(obj);
		delete obj;
	}

	for (int j = 0; j < collisionShapes.size(); j++) {
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}

	delete dynamicWorld;
	delete solver;
	delete overlappingPairCache;
	delete dispacher;
	delete collisionConfiguration;

	collisionShapes.clear();
}

Component* Physics_System::CreateRigidbody(glm::vec3 position, float RBmass) {
	
	Rigidbody r = Rigidbody(btVector3(position.x,position.y,position.z), RBmass);
	ListOfRigidbodies.push_back(r);
	return &ListOfRigidbodies.back();
}

Component* Physics_System::CreateCollider(glm::vec3 axisExtents) {
	Collider c = Collider(btVector3(axisExtents.x, axisExtents.y, axisExtents.z));
	ListOfColliders.push_back(c);
	return &ListOfColliders.back();
}

//btBoxShape* groundShape = new btBoxShape(btVector3(50., 50., 50.));

//collisionShapes.push_back(groundShape);
//btTransform groundTransform;
//groundTransform.setIdentity();
//groundTransform.setOrigin(btVector3(0, -56, 0));

//btScalar mass(0.);

//bool isDynamic = (mass != 0.f);
//btVector3 localInertia(0, 0, 0);
//if (isDynamic) {
//	groundShape->calculateLocalInertia(mass, localInertia);
//}
//btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
//btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
//btRigidBody* body = new btRigidBody(rbInfo);

//dynamicWorld->addRigidBody(body);