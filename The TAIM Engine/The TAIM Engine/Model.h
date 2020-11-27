#pragma once
#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>

// a Model is an object that holds all of the information about the imported 3D file. 
// it works by loading the full file, and only getting the first mesh that exists within it.
// this is for simplistic cases.
class Model
{
public:
	Model(std::string path, bool FlipImage, Shader* shader)
	{
		Flip = FlipImage;
		this->shader = shader;
		loadModel(path);
	}
	Model() {};
	~Model();

	std::string GetFileName();
	Mesh GetMesh();

private:
	Mesh RootMesh;
	std::string directory;
	std::vector<Texture> textures_loaded;
	Shader* shader;
	bool Flip;

	// loads the Model
	void loadModel(std::string path);

	// processes Nodes (small classes which detail the mesh and texture they are connected to.
	void processNode(aiNode* node, const aiScene* scene);

	// process the mesh into VAO,VBO and EBO
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	// loads the textures used for the model and assigns them to the Model.
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(char* path, std::string& directory);

};

