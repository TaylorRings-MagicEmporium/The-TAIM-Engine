#pragma once
#include <vector>
#include "Entity_System.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <bullet3/btBulletDynamicsCommon.h>

struct GPWrapItem {
	glm::vec3 Position;
	glm::quat Rotation;
	Entity* entity;
};

class Communication_Layer
{
private:


public:
	std::vector<GPWrapItem> GPBuffer;
	glm::vec3 Debug_Line_Vertices[512];
	//glm::vec3 Debug_
	int Debug_Line_Vertices_Counter = 0;
	Communication_Layer();
	void GPWrap(btTransform trans, Entity* entity);

	void ResetBuffers();
};

