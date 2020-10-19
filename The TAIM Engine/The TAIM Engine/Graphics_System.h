#pragma once
#include <vector>
#include "MeshRenderer.h"
#include "Shader.h"

#include "EventQueue.h"
#include "Event.h"

// the graphics system is responsible for the handling and executing of components that give a display onto the screen
class Graphics_System {
private:
	// holds the vector of MeshRenderer components
	std::vector<MeshRenderer> ListOfMeshRenderers;
public:
	// the initialisation of the Graphics system which needs to maximum number of components allowed.
	Graphics_System(int ComponentSize);

	// creates a mesh renderer that is capable of displaying something on the screen.
	// it returns the pointer of it the the entity that required it.
	MeshRenderer* CreateMeshRenderer(std::string path, Shader* shader, bool flip);
	
	// setups the graphics engine
	void Setup();

	// draws everything on to the screen.
	void Draw();

	// Update will cause the graphics system to do its generic procedure and poll the events related to it.
	void Update(EventQueue* EQ);

	// resets the frame so that it's cleared for the next iteration of draws
	void ResetGraphics();

	// destroys the system
	~Graphics_System();


	//specific event handlers for event testing

	//int MoveLeft(Event* e);
	//int MoveRight(Event* e);
	//int MoveUp(Event* e);
	//int MoveDown(Event* e);
	void Move(Event* e);
	void Reset(Event* e);


};