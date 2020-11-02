#pragma once
#include "Entity_System.h"
#include <iostream>
#include <vector>

// the event type explains what kind of event this is.
enum class EventType {
	//Physics_Engine
	MoveForward,MoveBackward,MoveLeft,MoveRight,Jump};

// the system enum is used to indicate which system should react to this specific event.
enum class Systems {Windows, Graphics, Physics, Audio};

// the Event is a special container that is essential for the communication of systems by storing information needed for systems to evaluate it.
class Event
{
protected:
	EventType MyType;
public:
	Event() {};
	std::vector<Entity*> ListOfEntities;
	bool SystemList[4];

	EventType GetType(){ return MyType; };
};

class Move : public Event {
public:
	glm::vec3 MoveAmount = glm::vec3(0);
	Move() {
		//std::cout << "I'm here!" << std::endl;
		SystemList[(int)Systems::Physics] = true;
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
		SystemList[(int)Systems::Physics] = true;
	}

	glm::vec3 JumpAmount = glm::vec3(0, 30, 0);
};

//class MoveObject : public Event {
//
//public:
//	MoveObject() { MyType = EventType::MoveObject; };
//
//	glm::vec3 PositionAdd = glm::vec3(0,0,0);
//};
//
//class Reset : public Event {
//
//public:
//	Reset() { MyType = EventType::Reset; };
//
//};

