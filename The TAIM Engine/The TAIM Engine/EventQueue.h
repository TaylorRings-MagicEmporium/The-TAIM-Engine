#pragma once
#include "Event.h"
#include <vector>
#include <iostream>

// the event queue is essential for keeping track of different events for the program
// for simplicity sake, only one event queue should be made so that the systems see the same even queue.
class EventQueue
{
private:
	std::vector<Event*> EventsList;
	// the EventCounter is useful for keeping the poll counter from a system
	int EventCounter = 0;
public:
	// initialisation of the event queue
	EventQueue();

	// add an event to the queue
	void AddEventToStack(Event* e);

	// a special function which allows a system to poll through the events of the queue
	// the return is either an event, or a nullptr, depicting that all events have been polled.
	Event* PollEvents(SubSystemType s);
	
	// this function updates the queue by removing events that no longer need a system reaction.
	void RemoveEmptyEvents();

	// this just returns the number of events in the queue.
	inline int GetTotalEvents() { return EventsList.size(); };

	void ResetQueue();
};

