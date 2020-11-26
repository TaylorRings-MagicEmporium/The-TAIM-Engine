#include "Graphics_System.h"


Graphics_System::Graphics_System() {



}

Graphics_System::~Graphics_System() {

}

MeshRenderer* Graphics_System::CreateMeshRenderer(std::string path, Shader* shader, bool flip) {
	MeshRenderer R = MeshRenderer(MR.SetModel(path, flip, shader),shader);
	ListOfMeshRenderers.push_back(R);
	return &ListOfMeshRenderers.back();
}

void Graphics_System::SetComponentSize(int size) {
	// if the list was not reserved, then this will cause a game breaking issue of pointers becoming null.
	ListOfMeshRenderers.reserve(size);
}

void Graphics_System::Startup()
{
	glEnable(GL_DEPTH_TEST);


	for (int i = 0; i < ListOfMeshRenderers.size(); i++) {
		ListOfMeshRenderers[i].Setup();
	}

	s = SR->GetShader("DebugLine");
	glGenVertexArrays(1, &DebugVAO);
	glGenBuffers(1, &DebugVBO);

	glBindVertexArray(DebugVAO);

	glBindBuffer(GL_ARRAY_BUFFER, DebugVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 500, Comm_Layer->Debug_Line_Vertices, GL_STREAM_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Comm_Layer->Debug_Line_Vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Graphics_System::ShutDown()
{
	ListOfMeshRenderers.clear();
}

void Graphics_System::Update() {

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

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	typedef void (Graphics_System::* method_function)(Event*);
	method_function method_pointer[EVENT_TYPE_COUNT];
	method_pointer[(int)EventType::UpdateTransform] = &Graphics_System::UpdateTransformEv;
	//method_pointer[(int)EventType::GunShot] = &Graphics_System::GunShotFeedback;
	method_pointer[(int)EventType::AnimationEnd] = &Graphics_System::HideAnimatedComponent;
	while (Event* e = Event_Queue->PollEvents(SubSystemType::Graphics)) {
		method_function func = method_pointer[(int)e->GetType()];
		(this->*func)(e);
	}


	for (int i = 0; i < ListOfMeshRenderers.size(); i++) {
		ListOfMeshRenderers[i].model = glm::translate(glm::mat4(1.0), ListOfMeshRenderers[i].GO->transform.position);
		ListOfMeshRenderers[i].model *= glm::toMat4(ListOfMeshRenderers[i].GO->transform.Rotation);
		ListOfMeshRenderers[i].model = glm::scale(ListOfMeshRenderers[i].model, ListOfMeshRenderers[i].GO->transform.scale);
	}

	for (int i = 0; i < Comm_Layer->GPBuffer.size(); i++) {
		if (MeshRenderer* mr = (MeshRenderer*)Comm_Layer->GPBuffer[i].entity->GetComponent(ComponentType::MeshRenderer)) {
			mr->model = glm::translate(glm::mat4(1.0), Comm_Layer->GPBuffer[i].entity->transform.position);
			mr->model *= glm::mat4(Comm_Layer->GPBuffer[i].entity->transform.Rotation);
			mr->model = glm::scale(mr->model, Comm_Layer->GPBuffer[i].entity->transform.scale);
		}
	}

	Draw();
	DebugDraw();
}

void Graphics_System::Draw() {

	for (int i = 0; i < ListOfMeshRenderers.size(); i++) {
		if (!ListOfMeshRenderers[i].hide) {
			ListOfMeshRenderers[i].Draw();
		}

	}
	//glUseProgram(NULL);
}

void Graphics_System::DebugDraw() {
	if (Comm_Layer->Debug_Line_Vertices_Counter > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, DebugVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, Comm_Layer->Debug_Line_Vertices_Counter * sizeof(glm::vec3), Comm_Layer->Debug_Line_Vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		s->Use();
		glBindVertexArray(DebugVAO);

		glDrawArrays(GL_LINES, 0, Comm_Layer->Debug_Line_Vertices_Counter);

		std::fill_n(Comm_Layer->Debug_Line_Vertices, Comm_Layer->Debug_Line_Vertices_Counter, glm::vec3(0.0));
		Comm_Layer->Debug_Line_Vertices_Counter = 0;
	}
}

void Graphics_System::UpdateTransformEv(Event* e) {
	UpdateTransform* m = (UpdateTransform*)(e);

	m->ListOfEntities[0]->transform.position = m->pos;
	m->ListOfEntities[0]->transform.Rotation = m->rot;
}

//void Graphics_System::GunShotFeedback(Event* e) {
//	//std::cout << "HIT!" << std::endl;
//	//for (int i = 0; i < e->ListOfEntities.size(); i++) {
//	//	ToggleHidingComponent(ComponentType::MeshRenderer,e->ListOfEntities[i]);
//	//}
//
//}

void Graphics_System::ToggleHidingComponent(ComponentType c, Entity* e) {
	e->GetComponent(c)->hide = !e->GetComponent(c)->hide;
}

void Graphics_System::HideAnimatedComponent(Event* e) {
	for (int i = 0; i < e->ListOfEntities.size(); i++) {
		ToggleHidingComponent(ComponentType::MeshRenderer, e->ListOfEntities[i]);
	}
}

void Graphics_System::ResetSystem() {
	ListOfMeshRenderers.clear();
}

void Graphics_System::SyncComponentsToSystem() {
	for (int i = 0; i < ListOfMeshRenderers.size(); i++) {
		ListOfMeshRenderers[i].Setup();
	}
}

