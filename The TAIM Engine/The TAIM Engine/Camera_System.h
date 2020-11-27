#pragma once
#include <iostream>
#include <vector>
#include "StaticCamera.h"
#include "FirstCamera.h"
#include "SubSystem.h"


// The Camera_System is responsible for managing the multiple cameras in the scene.
// for now, each scene needs a third person camera to operate fully. any other cameras can be added
// and swapped.
class Camera_System : public SubSystem
{
	glm::vec2 WindowSize;
	Camera* ActiveCamera;

	std::vector<Camera*> CameraList;
	int cameraCounter = 0;

	void SwapCamera(Event* e);
public:
	Camera_System();
	~Camera_System();

	void Startup();
	void ShutDown();
	void Update();
	void ResetSystem();
	void SetComponentSize(int size);
	void SetWindowSize(glm::vec2 size);
	Component* CreateStaticCamera(glm::vec3 target);
	void SetActiveCamera(Camera* ActCamera);
	Component* CreateFirstCamera(glm::vec3 offset);

};

