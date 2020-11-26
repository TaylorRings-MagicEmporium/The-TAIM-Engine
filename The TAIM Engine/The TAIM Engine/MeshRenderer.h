#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Component.h"
#include <vector>

//struct Vertex {
//	glm::vec3 Position;
//};

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

