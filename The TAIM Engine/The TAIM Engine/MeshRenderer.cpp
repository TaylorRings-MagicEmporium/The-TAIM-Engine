#include "MeshRenderer.h"
#include "model.h"
#include <glm/glm.hpp>

MeshRenderer::MeshRenderer(std::string path, Shader* shader, bool flip) {
	type = ComponentType::MeshRenderer;
	this->shader = shader;
	//shader->Use();
	Model t = Model(path, flip, this->shader);
	mesh = t.GetMesh();
}

void MeshRenderer::Setup() {
	//shader->Use();
	model = glm::translate(model, GO->pos);
	//glUseProgram(0);
}

void MeshRenderer::Draw() {
	shader->Use();
	shader->SetMat4("model", model);
	mesh.Draw(shader);


}