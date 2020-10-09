#include "MeshRenderer.h"
#include <glm/glm.hpp>

MeshRenderer::MeshRenderer(Shader* shader) {
	this->shader = shader;
}

void MeshRenderer::Setup() {

	shader->Use();

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//VBO data

	glm::vec3 vertexData[]{
		glm::vec3(-0.5f,-0.5f,0.0f),
		glm::vec3(0.5f,-0.5f,-1.0f),
		glm::vec3(0.0f,0.5f,0.0f)
	};

	for (int i = 0; i < 3; i++) {
		Vertex v;
		v.Position = vertexData[i];
		vertices.push_back(v);
	}

	//create VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Create VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	//assign Vertex data to specific locations in shaders
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glBindVertexArray(0);
}

void MeshRenderer::Draw() {
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	//Render quad

	//Bind program
	shader->Use();

	//Enable vertex position
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	//Disable vertex position
}