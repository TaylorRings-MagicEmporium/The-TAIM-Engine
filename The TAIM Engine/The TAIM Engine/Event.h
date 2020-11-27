#pragma once
#include <iostream>
#include <vector>
#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

// the event type explains what kind of event this is.
enum class EventType {
	//Physics_Engine
	MoveForward,MoveBackward,MoveLeft,MoveRight,Jump, ResetTransform,
	UpdateTransform, GunShot, ChangeCamera, AnimationBegin, AnimationEnd,
	ChangeLevel,HideComponent,
	
	PlaySoundEv};

// the system enum is used to indicate which system should react to this specific event.
enum class SubSystemType {Windows, Graphics, Physics, Audio, Network, System, Camera, EntityS, Animation};

//for effective function pointing, the size of the EventType has to be recorded.
const int EVENT_TYPE_COUNT = 14;


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
		MyType = EventType::PlaySoundEv;
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

class Gunshot : public Event {
public:
	Gunshot() {
		MyType = EventType::GunShot;
	}
	Entity* startEntity;
	glm::vec3 startingPoint;
	glm::vec3 direction;
	float length = 100;
	std::string tagToReact = "//";
};

class ChangeCamera : public Event {
public:
	ChangeCamera() {
		MyType = EventType::ChangeCamera;
		SubSystemOrder.push_back(SubSystemType::Camera);
	}

};

class Animation : public Event {
public:
	Animation() {};
};

class AnimationBegin : public Animation {
public:
	AnimationBegin() { MyType = EventType::AnimationBegin; };
};

class AnimationEnd : public Animation {
public:
	AnimationEnd() { MyType = EventType::AnimationEnd; };
};

class ChangeLevel : public Event {
public:
	ChangeLevel() { MyType = EventType::ChangeLevel; };
	int level = 0;
};

class HideComponent : public Event {
public:
	HideComponent() { MyType = EventType::HideComponent; };
};


