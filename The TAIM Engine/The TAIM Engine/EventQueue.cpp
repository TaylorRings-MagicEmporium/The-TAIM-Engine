#include "EventQueue.h"


EventQueue::EventQueue() {

}

void EventQueue::AddEventToStack(Event e) {
	EventsList.push_back(e);
}

int EventQueue::PollEvents(Event* e) {
	for (int a = EventCounter; a < EventsList.size(); a++) {
		e = &EventsList[a];
		EventCounter = a;
		return 1;
	}
	EventCounter = 0;
	return 0;
}

void EventQueue::RemoveEmptyEvents() {
	for (std::vector<Event>::iterator it = EventsList.begin(); it != EventsList.end(); it++) {
		bool destroy = true;
		for (int i = 0; i < 4; i++) {
			if ((*it).SystemList[i] == true) {
				destroy = false;
				break;
			}
		}
		if (destroy) {
			std::cout << "EVENT CLOSED" << std::endl;
			EventsList.erase(it);
		}
	}
}