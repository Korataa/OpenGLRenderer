#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <string>

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
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	std::vector<int> indices;

	Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<int> indices);
private:

};