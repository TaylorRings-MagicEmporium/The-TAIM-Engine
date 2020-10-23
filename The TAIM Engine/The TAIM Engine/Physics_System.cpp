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

	typedef void (Physics_System::* method_function)(Event*);
	method_function method_pointer[5];
	method_pointer[0] = &Physics_System::MoveForward;
	method_pointer[1] = &Physics_System::MoveBackward;
	method_pointer[2] = &Physics_System::MoveLeft;
	method_pointer[3] = &Physics_System::MoveRight;
	method_pointer[4] = &Physics_System::FJump;


	while (Event* e = EQ->PollEvents()) {
		if (e->SystemList[(int)Systems::Physics]) {
			method_function func = method_pointer[(int)e->GetType()];
			(this->*func)(e);
			e->SystemList[(int)Systems::Physics] = false;
		}
	}

	dynamicWorld->stepSimulation(1.0f / 60.0f, 10);

	for (int j = 0; j < ListOfRigidbodies.size(); j++) {
		btTransform trans;
		if (ListOfRigidbodies[j].body && ListOfRigidbodies[j].body->getMotionState()) {
			ListOfRigidbodies[j].body->getMotionState()->getWorldTransform(trans);
			CL->GPWrap(trans, ListOfRigidbodies[j].GO);
			if (j == 0) {
				//printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));

			}

		}

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

void Physics_System::MoveForward(Event* e) {
	Move* m = (Move*)(e);
	for (int i = 0; i < m->ListOfEntities.size(); i++) {
		Rigidbody* r = (Rigidbody*)m->ListOfEntities[i]->GetComponent(ComponentType::Rigidbody);
		r->body->activate(true);
		r->body->applyCentralForce(btVector3(m->MoveAmount.x, m->MoveAmount.y, m->MoveAmount.z));
	}
}
void Physics_System::MoveLeft(Event* e) {
	Move* m = (Move*)(e);
	for (int i = 0; i < m->ListOfEntities.size(); i++) {
		Rigidbody* r = (Rigidbody*)m->ListOfEntities[i]->GetComponent(ComponentType::Rigidbody);
		r->body->activate(true);
		r->body->applyCentralForce(btVector3(m->MoveAmount.x, m->MoveAmount.y, m->MoveAmount.z));
		//r->body->applyCentralImpulse(btVector3(m->MoveAmount.x, m->MoveAmount.y, m->MoveAmount.z));
		//r->body->applyCentralPushImpulse(btVector3(m->MoveAmount.x, m->MoveAmount.y, m->MoveAmount.z));
		//r->body->applyForce(btVector3(m->MoveAmount.x, m->MoveAmount.y, m->MoveAmount.z), btVector3(0, 0, 0));
	}
}
void Physics_System::MoveBackward(Event* e) {
	Move* m = (Move*)(e);
	for (int i = 0; i < m->ListOfEntities.size(); i++) {
		Rigidbody* r = (Rigidbody*)m->ListOfEntities[i]->GetComponent(ComponentType::Rigidbody);
		r->body->activate(true);

		r->body->applyCentralForce(btVector3(m->MoveAmount.x, m->MoveAmount.y, m->MoveAmount.z));
	}
}
void Physics_System::MoveRight(Event* e) {
	Move* m = (Move*)(e);
	for (int i = 0; i < m->ListOfEntities.size(); i++) {
		Rigidbody* r = (Rigidbody*)m->ListOfEntities[i]->GetComponent(ComponentType::Rigidbody);
		r->body->activate(true);

		r->body->applyCentralForce(btVector3(m->MoveAmount.x, m->MoveAmount.y, m->MoveAmount.z));
	}
}
void Physics_System::FJump(Event* e) {
	Jump* m = (Jump*)(e);
	for (int i = 0; i < m->ListOfEntities.size(); i++) {
		Rigidbody* r = (Rigidbody*)m->ListOfEntities[i]->GetComponent(ComponentType::Rigidbody);
		r->body->activate(true);
		r->body->applyCentralForce(btVector3(m->JumpAmount.x, m->JumpAmount.y, m->JumpAmount.z));
	}
}