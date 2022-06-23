#include "../include/Model.h"

Model::Model(std::string path)
{
	load(path);
}

void Model::load(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene)
	{
		std::cout << "Error->ASSIMP" << std::endl;
	}


}

void Model::loadNode(aiScene* scene, aiNode* node)
{
	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->loadMesh(scene, mesh));
	}

	//Handle the children
	for (int i = 0; i < node->mNumChildren; i++)
	{
		this->loadNode(scene, node->mChildren[i]);
	}
}

Mesh Model::loadMesh(aiScene* scene, aiMesh* mesh)
{
	std::vector<Vertex> vertices;
	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;

		if (mesh->mTextureCoords[0])
		{
			vertex.textureCoordinates.x = mesh->mTextureCoords[0][i].x;
			vertex.textureCoordinates.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			vertex.textureCoordinates = glm::vec2(0.0);
		}

		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.y = mesh->mNormals[i].z;

		vertices.push_back(vertex);
	}
}