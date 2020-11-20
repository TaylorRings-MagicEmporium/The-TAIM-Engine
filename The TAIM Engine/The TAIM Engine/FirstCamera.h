#pragma once
#include "Camera.h"
class FirstCamera : public Camera
{
private:

	glm::vec3 Offset;

public:
	glm::vec3 EyePoint;
	glm::vec3 CamDirection;
	void Setup();
	void SetOffset(glm::vec3 off);
	void UpdateCamera(glm::vec2 size);
};

