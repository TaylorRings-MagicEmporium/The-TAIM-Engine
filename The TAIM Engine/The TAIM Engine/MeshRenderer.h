#pragma once
#include "Shader.h"
class MeshRenderer
{
private:
	unsigned int VAO;
	unsigned int VBO;
	Shader* shader;
	unsigned int gVertexPos2DLocation;
public:
	MeshRenderer(Shader* shader);
	void Setup();
	void Draw();

};

