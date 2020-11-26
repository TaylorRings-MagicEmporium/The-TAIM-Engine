#include "Model_Registry.h"

Model_Registry::Model_Registry()
{
}

Model* Model_Registry::SetModel(std::string PathName, bool flip, Shader* shader)
{
	if (!ModelList.count(PathName)) {
		ModelList[PathName] = Model(PathName, flip, shader);

	}
	return &ModelList[PathName];

}

