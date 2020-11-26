#include "Entity.h"


Entity::Entity(glm::vec3 StartingPosition, glm::quat StartingRotation, glm::vec3 StartingScale, std::string tag, std::string FileTag, std::string name ) {
	transform.position = StartingPosition;
	transform.Rotation = StartingRotation;
	transform.scale = StartingScale;

	transform.defaultPosition = StartingPosition;
	transform.defaultRotation = StartingRotation;
	transform.defaultScale = StartingScale;

	this->Tag = tag;
	this->FileTag = FileTag;
	this->name = name;
}
Entity::Entity() {
	transform.position = glm::vec3(0);
	transform.Rotation = glm::quat(1,0,0,0);
	transform.scale = glm::vec3(1);

	transform.defaultPosition = glm::vec3(0);
	transform.defaultRotation = glm::quat(1, 0, 0, 0);
	transform.defaultScale = glm::vec3(1);

}

void Entity::SetComponent(Component* com) {
	ComponentList[com->type] = com;
	com->GO = this;
}

Component* Entity::GetComponent(ComponentType t) {
	return ComponentList[t];
}