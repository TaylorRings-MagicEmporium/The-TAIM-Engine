#pragma once
#include <vector>
#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <bullet3-3.0.6/btBulletDynamicsCommon.h>

struct GPWrapItem { // a graphics physics wrapper that stores the transform of the entity and the entity itself.
	glm::vec3 Position;
	glm::quat Rotation;
	Entity* entity;
};

// the Communication_Layer stores and exchanges data between different sub-systems. for now, GLM is needed to store
// mathematic data and functions.
class Communication_Layer
{
private:


public:
	std::vector<GPWrapItem> GPBuffer;
	glm::vec3 Debug_Line_Vertices[512];

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 UIProj = glm::mat4(1.0f);

	bool CanChangeLevel = true;
	int CurrentLevel = 0;
	int Debug_Line_Vertices_Counter = 0;
	Communication_Layer();
	void GPWrap(btTransform trans, Entity* entity);
	// resets the buffers
	void ResetBuffers();
};

