#pragma once
#include "GraphicsEngine.h"
#include <vector>
class Mesh
{
public:
	unsigned int VBO;
	unsigned int VAO;
	std::vector<Vertex> vertices;
	Mesh(std::vector<Vertex> vertices);
	~Mesh();
	void setup();
	void drawMesh();
};

