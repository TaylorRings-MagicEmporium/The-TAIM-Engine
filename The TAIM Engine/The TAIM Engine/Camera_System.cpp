#include "Camera_System.h"

Camera_System::Camera_System() {

}

Camera_System::~Camera_System() {

}

void Camera_System::Startup() {

}

void Camera_System::SetComponentSize(int size) {
	CameraList.reserve(100);
}

void Camera_System::Update() {
	if (ActiveCamera != nullptr) {
		ActiveCamera->UpdateCamera(WindowSize);
		Comm_Layer->proj = ActiveCamera->GetProj();
		Comm_Layer->UIProj = ActiveCamera->GetUIProj();
		Comm_Layer->view = ActiveCamera->GetView();
	}


	typedef void (Camera_System::* method_function)(Event*);
	method_function method_pointer[EVENT_TYPE_COUNT];
	method_pointer[(int)EventType::ChangeCamera] = &Camera_System::SwapCamera;

	while (Event* e = Event_Queue->PollEvents(SubSystemType::Camera)) {
		method_function func = method_pointer[(int)e->GetType()];
		(this->*func)(e);
	}
}

void Camera_System::ShutDown() {
	for (int i = 0; i < CameraList.size(); i++) {
		delete CameraList[i];
	}
	CameraList.clear();
}

void Camera_System::SetWindowSize(glm::vec2 size) {
	WindowSize = size;
}
Component* Camera_System::CreateStaticCamera(glm::vec3 target) {
	StaticCamera* c = new StaticCamera();
	c->SetValues(target);
	CameraList.push_back(c);
	ActiveCamera = CameraList.back();
	//Update();
	return CameraList.back();
}
void Camera_System::SetActiveCamera(Camera* ActCamera) {
	ActiveCamera = ActCamera;
}

Component* Camera_System::CreateFirstCamera(glm::vec3 offset) {
	FirstCamera* c = new FirstCamera();
	c->SetOffset(offset);
	CameraList.push_back(c);
	ActiveCamera = CameraList.back();
	return CameraList.back();
}

void Camera_System::SwapCamera(Event* e) {
	cameraCounter++;
	if (cameraCounter > CameraList.size() - 1) {
		cameraCounter = 0;
	}
	ActiveCamera = CameraList[cameraCounter];
}

void Camera_System::ResetSystem() {
	for (int i = 0; i < CameraList.size(); i++) {
		delete CameraList[i];
	}
	CameraList.clear();
	ActiveCamera = nullptr;
	cameraCounter = 0;
}
