#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>

struct Transform {
	glm::vec3 pos;
	glm::quat Rotation;
	glm::vec3 scale;

	glm::vec3 defaultPos;
	glm::vec3 defaultRot;
	glm::vec3 defaultScale;

	glm::vec3 forwardVector;
	glm::vec3 RightVector;
};