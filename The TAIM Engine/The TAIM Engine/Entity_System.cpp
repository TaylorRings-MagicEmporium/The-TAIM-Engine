#include "Entity_System.h"



Entity_System::Entity_System() {

}

Entity* Entity_System::CreateEntity(glm::vec3 Position, glm::quat Rotation, glm::vec3 Scale, std::string tag = "undefined", std::string FileTag = "undefined") {
	Entity* object = new Entity(Position, Rotation, Scale, tag, FileTag);
	ALL_ENTITIES.push_back(object);
	Tag_System[tag].push_back(object);
	return object;
}

std::vector<Entity*> Entity_System::GetEntitiesWithTag(std::string tag = "undefined") {

	if (Tag_System.count(tag) != 0) {
		return Tag_System[tag];
	}
	else {
		std::cout << "WARNING: no tag exist called < " << tag << " >. returning no entities" << std::endl;
	}
	return std::vector<Entity*>();
}

void Entity_System::CloseEntitySystem() {
	for (int i = 0; i < ALL_ENTITIES.size(); i++)
	{
		delete ALL_ENTITIES[i];
	}
	ALL_ENTITIES.clear();
	Tag_System.clear();
}

void Entity_System::Update() {
	for (int i = 0; i < Comm_Layer->GPBuffer.size(); i++) {
		Comm_Layer->GPBuffer[i].entity->transform.position = Comm_Layer->GPBuffer[i].Position;
		Comm_Layer->GPBuffer[i].entity->transform.Rotation = Comm_Layer->GPBuffer[i].Rotation;
	}

	for (int i = 0; i < ALL_ENTITIES.size(); i++) {
		if (ALL_ENTITIES[i]->transform.Rotation != glm::quat(1, 0, 0, 0)) {
			ALL_ENTITIES[i]->transform.forwardVector = glm::vec3(0, 0, -1) * ALL_ENTITIES[i]->transform.Rotation;
			ALL_ENTITIES[i]->transform.RightVector = glm::vec3(1, 0, 0) * ALL_ENTITIES[i]->transform.Rotation;
		}
	}

	typedef void (Entity_System::* method_function)(Event*);
	method_function method_pointer[EVENT_TYPE_COUNT];
	method_pointer[(int)EventType::GunShot] = &Entity_System::GunshotInfo;

	while (Event* e = Event_Queue->PollEvents(SubSystemType::EntityS)) {
		method_function func = method_pointer[(int)e->GetType()];
		(this->*func)(e);
	}
}

void Entity_System::GunshotInfo(Event* e)
{
	std::cout << "ENTITY SYSTEM: RECIEVED" << std::endl;
	Gunshot* g = (Gunshot*)(e);
	g->startingPoint = g->startEntity->transform.position + g->startEntity->transform.forwardVector + glm::vec3(0,0.6,0);
	g->direction = g->startEntity->transform.forwardVector;
}

void Entity_System::ResetSystem() {
	for (int i = 0; i < ALL_ENTITIES.size(); i++) {
		delete ALL_ENTITIES[i];
	}
	ALL_ENTITIES.clear();
	Tag_System.clear();

}