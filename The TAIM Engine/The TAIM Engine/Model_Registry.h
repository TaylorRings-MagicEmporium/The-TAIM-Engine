#pragma once
#include <map>
#include <string>
#include "Model.h"

// Model_Registry is a manager that stores models and only once
class Model_Registry
{
private:
	std::map<std::string, Model> ModelList;
public:
	Model_Registry();
	Model* SetModel(std::string PathName, bool flip, Shader* shader);
};

