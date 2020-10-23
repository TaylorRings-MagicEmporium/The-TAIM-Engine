#include "Entity.h"

Entity::Entity(glm::vec3 StartingPosition) { 
	pos = StartingPosition;
	rot = glm::quat(1, 0, 0, 0);
};

Entity::Entity(glm::vec3 StartingPosition, glm::quat StartingRotation) {
	pos = StartingPosition;
	rot = StartingRotation;
}
Entity::Entity(glm::quat StartingRotation) {
	pos = glm::vec3(0);
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