#pragma once
#include "Entity_System.h"
#include <iostream>
#include <vector>

// the event type explains what kind of event this is.
enum class EventType {
	//Physics_Engine
	MoveForward,MoveBackward,MoveLeft,MoveRight,Jump, ResetTransform,
	UpdateTransform,
	
	PlaySound};

// the system enum is used to indicate which system should react to this specific event.
enum class SubSystemType {Windows, Graphics, Physics, Audio, Network, System, Camera};

//for effective function pointing, the size of the EventType has to be recorded.
const int EVENT_TYPE_COUNT = 8;


// the Event is a special container that is essential for the communication of systems by storing information needed for systems to evaluate it.
class Event
{
protected:
	EventType MyType;
public:
	Event() {};
	std::vector<Entity*> ListOfEntities;
	std::vector<SubSystemType> SubSystemOrder;

	EventType GetType(){ return MyType; };
};

class Move : public Event {
public:
	glm::vec3 MoveAmount = glm::vec3(0);
	Move() {
		//std::cout << "I'm here!" << std::endl;
		SubSystemOrder.push_back(SubSystemType::Physics);
	}
};

class MoveForward : public Move {
public:
	MoveForward() {
		MyType = EventType::MoveForward;
		MoveAmount = glm::vec3(0, 0, -5);
	}
};

class MoveBackward : public Move {
public:
	MoveBackward() {
		MyType = EventType::MoveBackward;
		MoveAmount = glm::vec3(0, 0, 5);
	}
};

class MoveLeft : public Move {
public:
	MoveLeft() {
		MyType = EventType::MoveLeft;
		MoveAmount = glm::vec3(-5, 0, 0);
	}
};

class MoveRight : public Move {
public:
	MoveRight() {
		MyType = EventType::MoveRight;
		MoveAmount = glm::vec3(5, 0, 0);
	}
};

class Jump : public Event {
public:
	Jump() {
		MyType = EventType::Jump;
		SubSystemOrder.push_back(SubSystemType::Physics);
	}

	glm::vec3 JumpAmount = glm::vec3(0, 30, 0);
};

class PlaySoundEv : public Event {
public:
	PlaySoundEv() {
		MyType = EventType::PlaySound;
		SubSystemOrder.push_back(SubSystemType::Audio);
	}
};

class ResetTransform : public Event {
public:
	ResetTransform() {
		MyType = EventType::ResetTransform;
		SubSystemOrder.push_back(SubSystemType::Physics);
	}
};

class UpdateTransform : public Event {
public:
	UpdateTransform() {
		MyType = EventType::UpdateTransform;
		SubSystemOrder.push_back(SubSystemType::Graphics);
	}
	glm::vec3 pos;
	glm::quat rot;
};

