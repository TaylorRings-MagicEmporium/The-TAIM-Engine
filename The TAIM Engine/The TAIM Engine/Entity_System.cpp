#include "Entity_System.h"


Entity_System::Entity_System() {

}

Entity* Entity_System::CreateEntity(glm::vec3 Position, glm::quat Rotation, glm::vec3 Scale, std::string tag = "undefined", std::string FileTag = "undefined") {
	Entity* object = new Entity(Position, Rotation, Scale, tag, FileTag);
	ALL_ENTITIES.push_back(object);
	Tag_System[tag].push_back(object);
	return object;
}

std::vector<Entity*> Entity_System::GetEntitiesWithTag(std::string tag = "undefined") {

	if (Tag_System.count(tag) != 0) {
		return Tag_System[tag];
	}
	else {
		std::cout << "WARNING: no tag exist called < " << tag << " >. returning no entities" << std::endl;
	}
	return std::vector<Entity*>();
}

void Entity_System::CloseEntitySystem() {
	for (int i = 0; i < ALL_ENTITIES.size(); i++)
	{
		delete ALL_ENTITIES[i];
	}
	ALL_ENTITIES.clear();
	Tag_System.clear();
}