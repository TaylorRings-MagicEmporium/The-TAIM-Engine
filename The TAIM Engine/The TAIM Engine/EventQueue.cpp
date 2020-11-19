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
	for (std::vector<Event*>::iterator it = EventsList.begin(); it != EventsList.end(); it++) {
		if ((*it)->SubSystemOrder.size() != 0) {
			delete (*it);
			it++;
		}
	}

}