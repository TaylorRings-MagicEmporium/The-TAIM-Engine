#include "Communication_Layer.h"


Communication_Layer::Communication_Layer() {

};

void Communication_Layer::GPWrap(btTransform trans, Entity* entity) {
	GPWrapItem temp = GPWrapItem();
	temp.Position = glm::vec3(trans.getOrigin().getX(),trans.getOrigin().getY(),trans.getOrigin().getZ());
	temp.entity = entity;
	temp.Rotation = glm::quat(trans.getRotation().getW(), trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ());
	GPBuffer.push_back(temp);
}

void Communication_Layer::ResetBuffers() {
	GPBuffer.clear();
}