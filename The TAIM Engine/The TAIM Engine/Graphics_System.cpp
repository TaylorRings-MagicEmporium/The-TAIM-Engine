#include "Graphics_System.h"


Graphics_System::Graphics_System(int ComponentSize) {
	ListOfMeshRenderers.reserve(ComponentSize);
}

MeshRenderer* Graphics_System::CreateMeshRenderer(std::string path, Shader* shader, bool flip) {
	MeshRenderer MR = MeshRenderer(path, shader, flip);
	ListOfMeshRenderers.push_back(MR);
	return &MR;
}

Graphics_System::~Graphics_System() {
	//for (int i = 0; i < ListOfMeshRenderers.size(); i++) {
	//	delete ListOfMeshRenderers[i];
	//}
	ListOfMeshRenderers.clear();
}

void Graphics_System::Update(EventQueue EQ) {

	//int(Graphics_System:: * MoveL)(Event e);
	//MoveL = &Graphics_System::MoveLeft;

	//int(Graphics_System:: * MoveR)(Event e);
	//MoveR = &Graphics_System::MoveLeft;

	//int(Graphics_System::* Move[])(Event) = { MoveL,MoveR };

	typedef int (Graphics_System::*method_Function)(Event*);
	method_Function method_pointer[2] = { &Graphics_System::MoveLeft, &Graphics_System::MoveRight };

	//Event* e;
	//while (EQ.PollEvents(e)) {
	//	if (e->SystemList[(int)Systems::Graphics]) {
	//		method_Function func = method_pointer[(int)e->type];
	//		(this->*func)(e);
	//		e->SystemList[(int)Systems::Graphics] = false;
	//	}

	//}
}

int Graphics_System::MoveLeft(Event* e) {
	std::cout << "EVENT RECIEVED" << std::endl;
	e->ListOfEntities[0]->pos += glm::vec3(0.1, 0, 0);
	return 1;
}

int Graphics_System::MoveRight(Event* e) {
	std::cout << "EVENT RECIEVED" << std::endl;
	e->ListOfEntities[0]->pos += glm::vec3(-0.1, 0, 0);
	return 1;
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