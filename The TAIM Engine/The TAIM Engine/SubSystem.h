#pragma once
#include "EventQueue.h"
#include "Communication_Layer.h"

// the Abstract Subsystem class contains functions that all subsystems could have.
class SubSystem
{
public:
	virtual void Startup() {};											// setup's the specific subsystem properties
	virtual void ShutDown() {};											// shutdown's the specific subsystem properties
	virtual void Update() {};											// update's the specific subsystem properties and do any event checking.
	virtual void LateUpdate() {};										// update's the specific subststem properties after the initial update.
	virtual void SetComponentSize(int Comsize) {};						// if the subsystem has components, this sets the initial size of the components vector, so that no empty pointer errors happen.
	virtual void ToggleHidingComponent(ComponentType c, Entity* e) {};	// toggles the visability of the component in the SubSystem of that entity.
	virtual void ResetSystem() {};										// resets the specific subsystems's properties (used for level refreshing)
	virtual void SyncComponentsToSystem() {};							// after resetting the systems, the components need to sync back to the systems

	void AssignLayers(EventQueue* EQ, Communication_Layer* CL) {		// this assigns the event queue and communcation layer that all subsystems should have access to.
		Event_Queue = EQ;
		Comm_Layer = CL;
	}
	EventQueue* Event_Queue;
	Communication_Layer* Comm_Layer;
};

