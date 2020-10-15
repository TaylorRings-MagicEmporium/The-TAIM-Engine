#pragma once
#include "Entity.h"
#include <vector>

// the event type explains what kind of event this is.
enum class EventType {MoveLeft, MoveRight, MoveUp, MoveDown};

// the system enum is used to indicate which system should react to this specific event.
enum class Systems {Windows, Graphics, Physics, Audio};

// the Event is a special container that is essential for the communication of systems by storing information needed for systems to evaluate it.
class Event
{
public:
	EventType type;
	std::vector<Entity*> ListOfEntities;
	bool SystemList[4];

};

