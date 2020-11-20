#pragma once
#include "EventQueue.h"
#include "Communication_Layer.h"

class SubSystem
{
public:
	virtual void Startup() {};
	virtual void ShutDown() {};
	virtual void Update() {};
	virtual void LateUpdate() {};
	virtual void SetComponentSize(int Comsize) {};
	virtual void ToggleHidingComponent(ComponentType c, Entity* e) {};
	
	void AssignLayers(EventQueue* EQ, Communication_Layer* CL) {
		Event_Queue = EQ;
		Comm_Layer = CL;
	}
	//void AssignComponentSize(int ComSize) {
	//	ComponentSize = ComSize;
	//}
	EventQueue* Event_Queue;
	Communication_Layer* Comm_Layer;
};

