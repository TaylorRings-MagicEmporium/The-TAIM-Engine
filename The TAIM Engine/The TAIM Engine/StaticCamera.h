#pragma once
#include "Camera.h"
class StaticCamera : public Camera
{
private:
	glm::vec3 target;
public:
	void UpdateCamera(glm::vec2 size);
	void Setup();
	void SetValues(glm::vec3 tar);
};

