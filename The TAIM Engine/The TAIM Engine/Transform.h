#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>

struct Transform {
	glm::vec3 position;
	glm::quat Rotation;
	glm::vec3 scale;

	glm::vec3 defaultPosition;
	glm::quat defaultRotation;
	glm::vec3 defaultScale;

	glm::vec3 forwardVector = glm::vec3(-1,0,0);
	glm::vec3 RightVector = glm::vec3(1,0,0);
};