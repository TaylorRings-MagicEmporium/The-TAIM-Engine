#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Component.h"
#include <vector>

// the MeshRenderer is a component that displays a model at the entity's transforms point.
class MeshRenderer : public Component
{
private:

	Mesh mesh;
	glm::vec4 Col;
public:
	glm::mat4 model = glm::mat4(1);
	Shader* shader;
	MeshRenderer(Model* t, Shader* shader);
	void SetCol(glm::vec4 colour);
	void Setup();
	void Draw();

};

