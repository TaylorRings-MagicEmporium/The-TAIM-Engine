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


	SetupRigidbodies();


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
	method_pointer[(int)EventType::GunShot] = &Physics_System::TestGunShot;


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
		t.setOrigin(btVector3(m->ListOfEntities[i]->transform.position.x, m->ListOfEntities[i]->transform.position.y, m->ListOfEntities[i]->transform.position.z));
		t.setRotation(btQuaternion(m->ListOfEntities[i]->transform.Rotation.w, m->ListOfEntities[i]->transform.Rotation.x, m->ListOfEntities[i]->transform.Rotation.y, m->ListOfEntities[i]->transform.Rotation.z));
		r->body->clearForces();
		
		r->body->setAngularVelocity(btVector3(0,0,0));
		r->body->setLinearVelocity(btVector3(0, 0, 0));
		r->body->setPushVelocity(btVector3(0, 0, 0));
		r->body->setTurnVelocity(btVector3(0, 0, 0));

		r->body->setWorldTransform(t);
		r->motionState->setWorldTransform(t);
	}
}

void Physics_System::TestGunShot(Event* e) {
	std::cout << "PHYSICS SYSTEM: RECIEVED" << std::endl;
	Gunshot* g = (Gunshot*)(e);
	btVector3 startPoint = btVector3(g->startingPoint.x, g->startingPoint.y, g->startingPoint.z);
	btVector3 EndPoint = startPoint + g->length * btVector3(g->direction.x, g->direction.y, g->direction.z);


	btCollisionWorld::ClosestRayResultCallback closestResults(startPoint, EndPoint);
	closestResults.m_flags |= btTriangleRaycastCallback::kF_FilterBackfaces;
	dynamicWorld->rayTest(startPoint, EndPoint, closestResults);

	bool success = false;

	for (int i = 0; i < ListOfRigidbodies.size(); i++) {
		if (ListOfRigidbodies[i].GO->GetTag() == g->tagToReact) {
			if (ListOfRigidbodies[i].body == closestResults.m_collisionObject) {

				g->ListOfEntities.push_back(ListOfRigidbodies[i].GO);
				ToggleHidingComponent(ComponentType::Rigidbody, ListOfRigidbodies[i].GO);
				g->SubSystemOrder.push_back(SubSystemType::Animation);
				g->SubSystemOrder.push_back(SubSystemType::Audio);
				Profiling_System::GetInstance()->IncrementPlayer1Hit();
				success = true;
				break;
			}
		}
	}

	if (!success) {
		std::cout << "NO HIT" << std::endl;
		g->SubSystemOrder.push_back(SubSystemType::Audio);
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

void Physics_System::ToggleHidingComponent(ComponentType c, Entity* e) {
	e->GetComponent(c)->hide = !e->GetComponent(c)->hide;
	
	HideAdjust(c, e);

}

void Physics_System::HideAdjust(ComponentType c, Entity* e) {

	if (c == ComponentType::Rigidbody) {
		if (e->GetComponent(c)->hide) {
			Rigidbody* r = (Rigidbody*)e->GetComponent(c);
			r->body->setCollisionFlags(r->body->getCollisionFlags() | btRigidBody::CF_DISABLE_VISUALIZE_OBJECT);
			dynamicWorld->removeRigidBody(r->body);

		}
		else {
			Rigidbody* r = (Rigidbody*)e->GetComponent(c);
			r->body->setCollisionFlags(r->body->getCollisionFlags() & ~btRigidBody::CF_DISABLE_VISUALIZE_OBJECT);
			dynamicWorld->addRigidBody(r->body);
		}
	}
}

void Physics_System::ResetSystem() {
	for (int i = 0; i < ListOfRigidbodies.size(); i++) {
		dynamicWorld->removeRigidBody(ListOfRigidbodies[i].body);
	}
	ListOfRigidbodies.clear();
	ListOfColliders.clear();

}

void Physics_System::SetupRigidbodies() {
	for (int i = 0; i < ListOfRigidbodies.size(); i++) {
		ListOfRigidbodies[i].Setup();
		ListOfRigidbodies[i].body->setRollingFriction(0.2);
		ListOfRigidbodies[i].body->setSpinningFriction(0.1);
		dynamicWorld->addRigidBody(ListOfRigidbodies[i].body);
	}
}

void Physics_System::SyncComponentsToSystem() {
	SetupRigidbodies();
}
