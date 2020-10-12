#pragma once
#include "Event.h"
#include <vector>
#include <iostream>
class EventQueue
{
private:
	std::vector<Event> EventsList;
	int EventCounter = 0;
	//std::vector<event
public:
	EventQueue();
	void AddEventToStack(Event e);
	Event* PollEvents();
	void RemoveEmptyEvents();

	inline int GetTotalEvents() { return EventsList.size(); };
};

