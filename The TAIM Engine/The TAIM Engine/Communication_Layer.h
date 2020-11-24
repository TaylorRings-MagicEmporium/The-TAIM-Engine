#pragma once
#include <vector>
#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <bullet3-3.0.6/btBulletDynamicsCommon.h>

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

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	glm::mat4 UIProj = glm::mat4(1.0f);

	//glm::vec3 Debug_
	int Debug_Line_Vertices_Counter = 0;
	Communication_Layer();
	void GPWrap(btTransform trans, Entity* entity);
	//void SetNetworkPlayerAndEnemy(std::string playTag, std::string EnemyTag)
	void ResetBuffers();
};

