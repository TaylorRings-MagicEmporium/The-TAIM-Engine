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
	unsigned int VAO;
	unsigned int VBO;
	Shader* shader;
	Mesh mesh;
public:
	MeshRenderer(std::string path, Shader* shader, bool flip);
	void Setup();
	void Draw();

};

