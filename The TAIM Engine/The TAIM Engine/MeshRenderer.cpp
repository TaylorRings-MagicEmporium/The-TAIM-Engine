#include "MeshRenderer.h"
#include "model.h"
#include <glm/glm.hpp>

MeshRenderer::MeshRenderer(Model* t, Shader* shader) {
	type = ComponentType::MeshRenderer;
	this->shader = shader;
	mesh = t->GetMesh();
}

void MeshRenderer::Setup() {
	
	model = glm::translate(model, GO->transform.position);
	model *= glm::toMat4(GO->transform.Rotation);
	model = glm::scale(model, GO->transform.scale);
}

void MeshRenderer::Draw() {
	shader->Use();
	shader->SetMat4("model", model);
	if (shader->name == "basic") {
		shader->SetVec4("ColourInput", Col);
	}
	mesh.Draw(shader);
}

void MeshRenderer::SetCol(glm::vec4 colour) {
	Col = colour;
}