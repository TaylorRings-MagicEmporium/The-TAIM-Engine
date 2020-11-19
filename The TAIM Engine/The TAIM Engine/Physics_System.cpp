#include "Physics_System.h"

//#include "bullet3/CommonInterfaces/CommonRigidBodyBase.h"

Physics_System::Physics_System()
{

}

void Physics_System::SetComponentSize(int size) {
	ListOfRigidbodies.reserve(size);
	ListOfColliders.reserve(size);
}

void Physics_System::Startup() {



	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispacher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver;

	dynamicWorld = new btDiscreteDynamicsWorld(dispacher, overlappingPairCache, solver, collisionConfiguration);

	dynamicWorld->setGravity(btVector3(0, -10, 0));



	for (int i = 0; i < ListOfRigidbodies.size(); i++) {
		ListOfRigidbodies[i].Setup();
		ListOfRigidbodies[i].body->setRollingFriction(0.2);
		ListOfRigidbodies[i].body->setSpinningFriction(0.1);
		dynamicWorld->addRigidBody(ListOfRigidbodies[i].body);
	}

	BDD.CL = Comm_Layer;
	dynamicWorld->setDebugDrawer(&BDD);
	dynamicWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
}
void Physics_System::ShutDown(){
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

void Physics_System::Update()
{

	typedef void (Physics_System::* method_function)(Event*);
	method_function method_pointer[EVENT_TYPE_COUNT];
	method_pointer[(int)EventType::MoveForward] = &Physics_System::MoveForward;
	method_pointer[(int)EventType::MoveBackward] = &Physics_System::MoveBackward;
	method_pointer[(int)EventType::MoveLeft] = &Physics_System::MoveLeft;
	method_pointer[(int)EventType::MoveRight] = &Physics_System::MoveRight;
	method_pointer[(int)EventType::Jump] = &Physics_System::FJump;
	method_pointer[(int)EventType::ResetTransform] = &Physics_System::ResetTransformEv;


	while (Event* e = Event_Queue->PollEvents(SubSystemType::Physics)) {
		method_function func = method_pointer[(int)e->GetType()];
		(this->*func)(e);
	}

	dynamicWorld->stepSimulation(1.0f / 60.0f, 10);

	//ColliderCallBack();

	dynamicWorld->debugDrawWorld();
	for (int j = 0; j < ListOfRigidbodies.size(); j++) {
		btTransform trans;
		if (ListOfRigidbodies[j].body && ListOfRigidbodies[j].body->getMotionState()) {
			ListOfRigidbodies[j].body->getMotionState()->getWorldTransform(trans);
			Comm_Layer->GPWrap(trans, ListOfRigidbodies[j].GO);
			//if (j == 0) {
			//	//printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));

			//}
		}
	}
}

Physics_System::~Physics_System()
{

}

Component* Physics_System::CreateRigidbody(glm::vec3 position, float RBmass) {
	
	Rigidbody r = Rigidbody(btVector3(position.x,position.y,position.z), RBmass);
	ListOfRigidbodies.push_back(r);
	return &ListOfRigidbodies.back();
}

Component* Physics_System::CreateCubeCollider(glm::vec3 axisExtents) {
	Collider c = CubeCollider(btVector3(axisExtents.x, axisExtents.y, axisExtents.z));
	ListOfColliders.push_back(c);
	return &ListOfColliders.back();
}

Component* Physics_System::CreateSphereCollider(float radius) {
	Collider c = SphereCollider(radius);
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

		//r->body->applyTorque(btVector3(m->MoveAmount.x, m->MoveAmount.y, m->MoveAmount.z));
		//r->body->applyTorque(btVector3(0, 1.4, 0));
		r->body->applyCentralForce(btVector3(m->MoveAmount.x, m->MoveAmount.y, m->MoveAmount.z));
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

void Physics_System::ResetTransformEv(Event* e) {
	ResetTransform* m = (ResetTransform*)(e);
	for (int i = 0; i < m->ListOfEntities.size(); i++) {
		Rigidbody* r = (Rigidbody*)m->ListOfEntities[i]->GetComponent(ComponentType::Rigidbody);
		r->body->activate(true);
		btTransform t;
		r->motionState->getWorldTransform(t);
		t.setOrigin(btVector3(m->ListOfEntities[i]->defaultPos.x, m->ListOfEntities[i]->defaultPos.y, m->ListOfEntities[i]->defaultPos.z));
		t.setRotation(btQuaternion(m->ListOfEntities[i]->defaultRot.w, m->ListOfEntities[i]->defaultRot.x, m->ListOfEntities[i]->defaultRot.y, m->ListOfEntities[i]->defaultRot.z));
		r->body->clearForces();
		
		r->body->setAngularVelocity(btVector3(0,0,0));
		r->body->setLinearVelocity(btVector3(0, 0, 0));
		r->body->setPushVelocity(btVector3(0, 0, 0));
		r->body->setTurnVelocity(btVector3(0, 0, 0));

		r->body->setWorldTransform(t);
		r->motionState->setWorldTransform(t);
	}
}

void Physics_System::ColliderCallBack() {
	btRigidBody* temp1 = ListOfRigidbodies[0].body;
	btRigidBody* temp2 = ListOfRigidbodies[1].body;
	BulletContactResultCallback a;
		dynamicWorld->contactPairTest(temp1, temp2, a);

	if (a.bCollision) {
		std::cout << "HIT" << std::endl;
	}
}