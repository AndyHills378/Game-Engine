#pragma once
#include <vector>
#include "Texture.h"
#include "TextReader.h"

class Mesh
{
public:
	TextReader obj;
	unsigned int VBO;
	unsigned int VAO;
	std::vector<Vertex> vertices;
	vec3 position, scale, rotateVec;
	float rotate;
	int meshID;
	bool model;
	bool LoadMesh;
	Mesh(std::vector<Vertex> vertices, vec3 position, float rotate, glm::vec3 rotateVec, int meshID);
	Mesh(char* filename, int meshID, glm::vec3 position, float rotate, glm::vec3 scale);
	~Mesh();
	void modelSetup();
	void setup();
	void drawMesh();
};

