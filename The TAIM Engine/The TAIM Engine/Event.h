#pragma once
#include "Entity.h"
#include <vector>

// the event type explains what kind of event this is.
enum class EventType {MoveObject, Reset};

// the system enum is used to indicate which system should react to this specific event.
enum class Systems {Windows, Graphics, Physics, Audio};

// the Event is a special container that is essential for the communication of systems by storing information needed for systems to evaluate it.
class Event
{
protected:
	EventType MyType;
public:
	//EventType type;
	std::vector<Entity*> ListOfEntities;
	bool SystemList[4];

	EventType GetType(){ return MyType; };
};

class MoveObjectEv : public Event {

public:
	MoveObjectEv() { MyType = EventType::MoveObject; };

	glm::vec3 PositionAdd = glm::vec3(0,0,0);
};

class ResetEv : public Event {

public:
	ResetEv() { MyType = EventType::Reset; };

};

