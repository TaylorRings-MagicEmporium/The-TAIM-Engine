#include "Physics_System.h"
//#include "bullet3/CommonInterfaces/CommonRigidBodyBase.h"

Physics_System::Physics_System(int ComponentSize)
{

}

void Physics_System::Setup()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispacher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver;

	dynamicWorld = new btDiscreteDynamicsWorld(dispacher, overlappingPairCache, solver, collisionConfiguration);

	dynamicWorld->setGravity(btVector3(0, -10, 0));

	//ground plane
	{
		btBoxShape* groundShape = new btBoxShape(btVector3(50., 50., 50.));

		collisionShapes.push_back(groundShape);
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -56, 0));

		btScalar mass(0.);

		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0, 0, 0);
		if (isDynamic) {
			groundShape->calculateLocalInertia(mass, localInertia);
		}
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		dynamicWorld->addRigidBody(body);
	}

	// normal object
	{
		btBoxShape* groundShape = new btBoxShape(btVector3(1.,1.,1.));

		collisionShapes.push_back(groundShape);
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, 10, 0));

		btScalar mass(1.);

		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0, 0, 0);
		if (isDynamic) {
			groundShape->calculateLocalInertia(mass, localInertia);
		}
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		dynamicWorld->addRigidBody(body);
	}
}

void Physics_System::Update(EventQueue* EQ)
{
	dynamicWorld->stepSimulation(1.0f / 60.0f, 10);
	for (int j = dynamicWorld->getNumCollisionObjects() - 1; j >= 0; j--) {
		btCollisionObject* obj = dynamicWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState()) {
			body->getMotionState()->getWorldTransform(trans);
		}
		else {
			trans = obj->getWorldTransform();
		}
		printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
	}
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
