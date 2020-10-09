#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "Shader.h"

// this records the the vertex information from the file.
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

// this records the texture id, type and directory path
struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

// the Mesh contains all of the information needed (vertex, textures) to draw itself, making it modular independent in run-time.
class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	std::string name;

	Mesh() {};
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader* shader);
	~Mesh();

private:
	unsigned int VAO, VBO, EBO;

	void setupMesh();

};

