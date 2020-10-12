#include "EventQueue.h"


EventQueue::EventQueue() {

}

void EventQueue::AddEventToStack(Event e) {
	EventsList.push_back(e);
}

Event* EventQueue::PollEvents() {
	for (int a = EventCounter; a < EventsList.size(); a++) {
		
		EventCounter = a+1;
		return &EventsList[a];
		//return 1;
	}
	EventCounter = 0;
	return nullptr;
}

void EventQueue::RemoveEmptyEvents() {
	std::vector<Event> NewList;
	for (std::vector<Event>::iterator it = EventsList.begin(); it != EventsList.end(); it++) {
		bool destroy = true;
		for (int i = 0; i < 4; i++) {
			if ((*it).SystemList[i] == true) {
				destroy = false;
				break;
			}
		}
		if (destroy) {
			//std::cout << "EVENT CLOSED" << std::endl;
			//EventsList.erase(it);
			continue;
		}
		else {
			NewList.push_back(*it);
		}
	}

	EventsList.clear();
	EventsList = NewList;

}