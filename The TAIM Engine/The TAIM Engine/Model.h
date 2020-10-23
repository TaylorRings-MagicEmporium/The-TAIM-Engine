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
class Model
{
public:
	Model(std::string path, bool FlipImage, Shader* shader)
	{
		Flip = FlipImage;
		this->shader = shader;
		loadModel(path);
	}

	~Model();

	std::string GetFileName();
	Mesh GetMesh();

private:
	Mesh RootMesh;
	std::string directory;
	std::vector<Texture> textures_loaded;
	Shader* shader;
	bool Flip;


	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(char* path, std::string& directory);

};

