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

void Graphics_System::Update(EventQueue* EQ) {

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

	typedef void (Graphics_System::* method_function)(Event*);
	method_function method_pointer[EVENT_TYPE_COUNT];
	method_pointer[(int)EventType::UpdateTransform] = &Graphics_System::UpdateTransformEv;

	while (Event* e = EQ->PollEvents()) {
		if (e->SystemList[(int)Systems::Graphics]) {
			method_function func = method_pointer[(int)e->GetType()];
			(this->*func)(e);
			e->SystemList[(int)Systems::Graphics] = false;
		}
	}


	for (int i = 0; i < ListOfMeshRenderers.size(); i++) {
		ListOfMeshRenderers[i].model = glm::translate(glm::mat4(1.0), ListOfMeshRenderers[i].GO->pos);
		ListOfMeshRenderers[i].model *= glm::toMat4(ListOfMeshRenderers[i].GO->rot);
		ListOfMeshRenderers[i].model = glm::scale(ListOfMeshRenderers[i].model, ListOfMeshRenderers[i].GO->scale);
	}

	for (int i = 0; i < CL->GPBuffer.size(); i++) {
		if (MeshRenderer* mr = (MeshRenderer*)CL->GPBuffer[i].entity->GetComponent(ComponentType::MeshRenderer)) {
			CL->GPBuffer[i].entity->pos = CL->GPBuffer[i].Position;
			mr->model = glm::translate(glm::mat4(1.0), CL->GPBuffer[i].entity->pos);
			CL->GPBuffer[i].entity->rot = CL->GPBuffer[i].Rotation;
			mr->model *= glm::mat4(CL->GPBuffer[i].entity->rot);
			mr->model = glm::scale(mr->model, CL->GPBuffer[i].entity->scale);
		}
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

	s = SR->GetShader("DebugLine");
	glGenVertexArrays(1, &DebugVAO);
	glGenBuffers(1, &DebugVBO);

	glBindVertexArray(DebugVAO);

	glBindBuffer(GL_ARRAY_BUFFER, DebugVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 500, CL->Debug_Line_Vertices, GL_STREAM_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CL->Debug_Line_Vertices[0]), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Graphics_System::ResetGraphics() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics_System::DebugDraw() {
	if (CL->Debug_Line_Vertices_Counter > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, DebugVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, CL->Debug_Line_Vertices_Counter * sizeof(glm::vec3), CL->Debug_Line_Vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//float debugColor[4];
		//debugColor[0] = m_currentLineColor.x();
		//debugColor[1] = m_currentLineColor.y();
		//debugColor[2] = m_currentLineColor.z();
		//debugColor[3] = 1.f;

		s->Use();
		glBindVertexArray(DebugVAO);

		glDrawArrays(GL_LINES, 0, CL->Debug_Line_Vertices_Counter);

		std::fill_n(CL->Debug_Line_Vertices, CL->Debug_Line_Vertices_Counter, glm::vec3(0.0));
		CL->Debug_Line_Vertices_Counter = 0;
	}
}

void Graphics_System::UpdateTransformEv(Event* e) {
	UpdateTransform* m = (UpdateTransform*)(e);

	m->ListOfEntities[0]->pos = m->pos;
	m->ListOfEntities[0]->rot = m->rot;
}