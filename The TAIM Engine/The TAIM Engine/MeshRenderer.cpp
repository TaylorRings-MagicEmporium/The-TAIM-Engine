#include "MeshRenderer.h"


MeshRenderer::MeshRenderer(Shader* shader) {
	this->shader = shader;
}

void MeshRenderer::Setup() {

	shader->Use();
	//bool success = true;
	//Get vertex attribute location
	gVertexPos2DLocation = glGetAttribLocation(shader->ID, "LVertexPos2D");

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//VBO data
	GLfloat vertexData[] =
	{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, -1.0f,
			0.0f,  0.5f, 0.0f
	};

	//create VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Create VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

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
	glEnableVertexAttribArray(gVertexPos2DLocation);

	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);

	//Set index data and render
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);


	glBindVertexArray(0);
	//Disable vertex position
	glDisableVertexAttribArray(gVertexPos2DLocation);
}