#pragma once
#include "Entity.h"
#include <vector>
enum class EventType {MoveLeft, MoveRight};
enum class Systems {Windows, Graphics, Physics, Audio};

class Event
{
public:
	EventType type;
	std::vector<Entity*> ListOfEntities;
	bool SystemList[4];



};

