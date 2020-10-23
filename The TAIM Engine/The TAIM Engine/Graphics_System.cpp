#include "Graphics_System.h"


Graphics_System::Graphics_System(int ComponentSize) {
	// if the list was not reserved, then this will cause a game breaking issue of pointers becoming null.
	ListOfMeshRenderers.reserve(ComponentSize);
}

MeshRenderer* Graphics_System::CreateMeshRenderer(std::string path, Shader* shader, bool flip) {
	MeshRenderer MR = MeshRenderer(path, shader, flip);
	ListOfMeshRenderers.push_back(MR);
	return &ListOfMeshRenderers.back();
}

Graphics_System::~Graphics_System() {
	ListOfMeshRenderers.clear();
}

void Graphics_System::Update(EventQueue* EQ, Communication_Layer* CL) {

	// this is a special procedure to create member function pointers into an array
	//typedef void (Graphics_System::* method_Function)(Event*);
	//method_Function method_pointer[4];
	//method_pointer[0] = &Graphics_System::Move;
	//method_pointer[1] = &Graphics_System::Reset;

	// how it works:
	// 1. goes through each event using PollEvents(). if it's null, then it will exit the while loop.
	// 2. checks if the event needs this particular system
	// 3. if so, using the function pointers and the enum class in events, it would call the approproate event based on the index.
	// 4. finally, cross the event's system reaction for this system to false, as this engine has done what it needed to do.

	//while (Event* e = EQ->PollEvents()) {
	//	if (e->SystemList[(int)Systems::Graphics]) {
	//		method_Function func = method_pointer[(int)e->GetType()];
	//		(this->*func)(e);
	//		e->SystemList[(int)Systems::Graphics] = false;
	//	}
	//}

	for (int i = 0; i < CL->GPBuffer.size(); i++) {
		if (MeshRenderer* mr = (MeshRenderer*)CL->GPBuffer[i].entity->GetComponent(ComponentType::MeshRenderer)) {
			CL->GPBuffer[i].entity->pos = CL->GPBuffer[i].Position;
			mr->model = glm::translate(glm::mat4(1.0), CL->GPBuffer[i].entity->pos);
			CL->GPBuffer[i].entity->rot = CL->GPBuffer[i].Rotation;
			mr->model *= glm::mat4(CL->GPBuffer[i].entity->rot);
		}
		
		//mr->model *= glm::toMat4(CL->GPBuffer[i].Rotation);
	}
}

void Graphics_System::Draw() {

	for (int i = 0; i < ListOfMeshRenderers.size(); i++) {
		ListOfMeshRenderers[i].Draw();
	}
	//glUseProgram(NULL);
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