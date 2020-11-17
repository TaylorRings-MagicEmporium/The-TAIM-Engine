#pragma once
#include <iostream>
#include <vector>
#include "Camera.h"
#include "SubSystem.h"
enum class CameraTypes{FIRST,THIRD,STATIC, FREEFORM};

class Camera_System : public SubSystem
{
	glm::vec2 WindowSize;
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
	Camera* ActiveCamera;

	std::vector<Camera> CameraList;
};

