#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <string>
#include "Shader.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
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
	std::vector<int> indices;

	void Draw(Shader shader);
	Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<int> indices);
private:
	//  render data
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};