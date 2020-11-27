#pragma once
#include "Camera.h"

// StaticCamera is a child of Camera that with the transform's positions, makes it look at a specific vector3 target.
class StaticCamera : public Camera
{
private:
	glm::vec3 target;
public:
	void UpdateCamera(glm::vec2 size);
	void Setup();
	void SetValues(glm::vec3 tar);
};

