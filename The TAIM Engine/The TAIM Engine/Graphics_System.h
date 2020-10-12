#pragma once
#include <vector>
#include "MeshRenderer.h"
#include "Shader.h"

#include "EventQueue.h"
#include "Event.h"

class Graphics_System {
private:
	std::vector<MeshRenderer> ListOfMeshRenderers;
public:
	Graphics_System(int ComponentSize);
	MeshRenderer* CreateMeshRenderer(std::string path, Shader* shader, bool flip);
	void Setup();
	void Draw();
	void Update(EventQueue* EQ);

	void ResetGraphics();
	~Graphics_System();

	int MoveLeft(Event* e);
	int MoveRight(Event* e);
	int MoveUp(Event* e);
	int MoveDown(Event* e);


};