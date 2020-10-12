#include "Entity.h"

Entity::Entity() {};

void Entity::SetComponent(Component* com) {
	ComponentList[com->type] = com;
}

Component* Entity::GetComponent(ComponentType t) {
	return ComponentList[t];
}