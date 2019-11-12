#pragma once
#include "GraphicsEngine.h"
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
	vec3 position, scale;
	float rotate;
	int meshID;
	bool model;
	bool LoadMesh;
	Mesh(std::vector<Vertex> vertices, vec3 position, float rotate, int meshID);
	Mesh(char* filename, int meshID, glm::vec3 position, glm::vec3 scale);
	~Mesh();
	void modelSetup();
	void setup();
	void drawMesh();
};

