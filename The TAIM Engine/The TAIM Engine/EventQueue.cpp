#include "EventQueue.h"


EventQueue::EventQueue() {

}

void EventQueue::AddEventToStack(Event* e) {
	EventsList.push_back(e);
}

Event* EventQueue::PollEvents(SubSystemType s) {
	for (int a = EventCounter; a < EventsList.size(); a++) {
		
		if (EventsList[a]->SubSystemOrder.size() != 0) {
			if (EventsList[a]->SubSystemOrder[0] == s) {
				EventsList[a]->SubSystemOrder.erase(EventsList[a]->SubSystemOrder.begin());
				EventCounter = a + 1;
				return EventsList[a];
			}
		}

		EventCounter = a + 1;
		//return 1;
	}
	EventCounter = 0;

	return nullptr;
}

void EventQueue::RemoveEmptyEvents() {
	std::vector<Event*> NewList;
	std::vector<Event*>::iterator it = EventsList.begin();
	for (std::vector<Event*>::iterator it = EventsList.begin(); it != EventsList.end(); it++) {
		bool destroy = true;
		if ((*it)->SubSystemOrder.size() != 0) {
			destroy = false;
		}
		if (destroy) {
			delete(*it);
			continue;
		}
		else {
			NewList.push_back(*it);
		}
	}

	EventsList.clear();
	EventsList = NewList;
}