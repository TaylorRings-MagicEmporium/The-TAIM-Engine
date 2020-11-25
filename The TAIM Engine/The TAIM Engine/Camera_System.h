#pragma once
#include <iostream>
#include <vector>
#include "StaticCamera.h"
#include "FirstCamera.h"
#include "SubSystem.h"



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
	void SetComponentSize(int size);
	void SetWindowSize(glm::vec2 size);
	Component* CreateStaticCamera(glm::vec3 target);
	void SetActiveCamera(Camera* ActCamera);
	Component* CreateFirstCamera(glm::vec3 offset);

};

