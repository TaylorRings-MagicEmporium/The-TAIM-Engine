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

public:
	glm::mat4 model = glm::mat4(1);
	Shader* shader;
	MeshRenderer(std::string path, Shader* shader, bool flip);
	void Setup();
	void Draw();

};

