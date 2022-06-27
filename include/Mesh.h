#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include "Shader.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bittangent;
	glm::vec2 textureCoordinates;
};

struct Texture
{
	unsigned int ID;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	std::vector<unsigned int> indices;

	void Draw(Shader& shader);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
private:
	//  render data
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};