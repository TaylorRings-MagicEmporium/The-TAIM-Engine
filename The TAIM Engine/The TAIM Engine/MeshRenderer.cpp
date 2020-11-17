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
	
	model = glm::translate(model, GO->pos);
	model *= glm::toMat4(GO->rot);
	model = glm::scale(model, GO->scale);
	//glUseProgram(0);
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