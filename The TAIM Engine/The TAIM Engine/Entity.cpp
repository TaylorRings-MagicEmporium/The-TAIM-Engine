#include "Entity.h"


Entity::Entity(glm::vec3 StartingPosition, glm::quat StartingRotation, glm::vec3 StartingScale, std::string tag) {
	pos = StartingPosition;
	rot = StartingRotation;
	scale = StartingScale;

	defaultPos = StartingPosition;
	defaultRot = StartingRotation;
	defaultScale = StartingScale;
}
Entity::Entity() {
	pos = glm::vec3(0);
	rot = glm::quat(1,0,0,0);
	scale = glm::vec3(1);

	defaultPos = glm::vec3(0);
	defaultRot = glm::quat(1, 0, 0, 0);
	defaultScale = glm::vec3(1);

}

void Entity::SetComponent(Component* com) {
	ComponentList[com->type] = com;
	com->GO = this;
}

Component* Entity::GetComponent(ComponentType t) {
	return ComponentList[t];
}