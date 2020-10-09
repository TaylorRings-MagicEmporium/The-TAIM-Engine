#pragma once
#include "Shader.h"
#include <vector>

struct Vertex {
	glm::vec3 Position;
};

class MeshRenderer
{
private:
	unsigned int VAO;
	unsigned int VBO;
	Shader* shader;
	std::vector<Vertex> vertices;
public:
	MeshRenderer(Shader* shader);
	void Setup();
	void Draw();

};

