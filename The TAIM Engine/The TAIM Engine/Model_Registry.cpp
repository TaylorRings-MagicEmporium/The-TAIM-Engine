#include "Model_Registry.h"

Model_Registry::Model_Registry()
{
}

Model* Model_Registry::SetModel(std::string PathName, bool flip, Shader* shader)
{
	// the whole model list implements a flyweight pattern, as only one type of mesh will be loaded from the files.
	if (!ModelList.count(PathName)) {
		ModelList[PathName] = Model(PathName, flip, shader); 

	}
	return &ModelList[PathName];

}

