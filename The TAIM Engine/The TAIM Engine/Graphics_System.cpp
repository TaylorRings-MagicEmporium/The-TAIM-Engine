#include "Graphics_System.h"


Graphics_System::Graphics_System(int ComponentSize) {
	// if the list was not reserved, then this will cause a game breaking issue of pointers becoming null.
	ListOfMeshRenderers.reserve(ComponentSize);
}

MeshRenderer* Graphics_System::CreateMeshRenderer(std::string path, Shader* shader, bool flip) {
	MeshRenderer MR = MeshRenderer(path, shader, flip);
	ListOfMeshRenderers.push_back(MR);
	return &MR;
}

Graphics_System::~Graphics_System() {
	ListOfMeshRenderers.clear();
}

void Graphics_System::Update(EventQueue* EQ) {

	// this is a special procedure to create member function pointers into an array
	typedef void (Graphics_System::*method_Function)(Event*);
	method_Function method_pointer[4]; 
	method_pointer[0] = &Graphics_System::Move;
	method_pointer[1] = &Graphics_System::Reset;

	// how it works:
	// 1. goes through each event using PollEvents(). if it's null, then it will exit the while loop.
	// 2. checks if the event needs this particular system
	// 3. if so, using the function pointers and the enum class in events, it would call the approproate event based on the index.
	// 4. finally, cross the event's system reaction for this system to false, as this engine has done what it needed to do.
	
	while (Event* e = EQ->PollEvents()) {
		if (e->SystemList[(int)Systems::Graphics]) {
			method_Function func = method_pointer[(int)e->GetType()];
			(this->*func)(e);
			e->SystemList[(int)Systems::Graphics] = false;
		}

	}
}

void Graphics_System::Move(Event* e) {
	MoveObjectEv* moe = (MoveObjectEv*)(e);
	if (moe->GetType() == EventType::MoveObject) {
		for (int i = 0; i < e->ListOfEntities.size(); i++) {
			moe->ListOfEntities[i]->PosChange += moe->PositionAdd;
		}
	}

}

void Graphics_System::Reset(Event* e) {
	ResetEv* re = (ResetEv*)(e);
	if (re->GetType() == EventType::Reset) {
		for (int i = 0; i < e->ListOfEntities.size(); i++) {
			re->ListOfEntities[i]->PosChange = glm::vec3(0);
		}
	}
}

void Graphics_System::Draw() {
	for (int i = 0; i < ListOfMeshRenderers.size(); i++) {
		ListOfMeshRenderers[i].Draw();
	}
}

void Graphics_System::Setup() {
	for (int i = 0; i < ListOfMeshRenderers.size(); i++) {
		ListOfMeshRenderers[i].Setup();
	}
}

void Graphics_System::ResetGraphics() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}