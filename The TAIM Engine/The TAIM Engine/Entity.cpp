#include "Entity.h"


Entity::Entity(glm::vec3 StartingPosition, glm::quat StartingRotation, std::string tag) {
	pos = StartingPosition;
	rot = StartingRotation;
}
Entity::Entity() {
	pos = glm::vec3(0);
	//w,x,y,z
	rot = glm::quat(1,0,0,0);
}

void Entity::SetComponent(Component* com) {
	ComponentList[com->type] = com;
	com->GO = this;
}

Component* Entity::GetComponent(ComponentType t) {
	return ComponentList[t];
}