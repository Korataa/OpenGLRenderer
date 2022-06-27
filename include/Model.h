#pragma once

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include <vector>
#include <string>

class Model
{
public:
	std::vector<Mesh> meshes;
	std::string modelDirectory;

	Model();
	Model(std::string path);
	void Draw(Shader& shader);
	void load(std::string path);
	void loadNode(const aiScene* scene, aiNode* node);
	Mesh loadMesh(const aiScene* scene, aiMesh* mesh);
	std::vector<Texture> loadTexturesFromMaterial(aiMaterial* material, aiTextureType type, std::string typeName);
	int loadTextureFromFile(std::string fileName);

};