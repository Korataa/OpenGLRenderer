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
	std::vector<Mesh> meshes;

	Model();
	Model(std::string path);
	void load(std::string path);
	void loadNode(aiScene* scene, aiNode* node);
	Mesh loadMesh(aiScene* scene, aiMesh* mesh);
};