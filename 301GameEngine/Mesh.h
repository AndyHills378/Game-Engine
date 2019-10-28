#pragma once
#include "GraphicsEngine.h"
#include <vector>
class Mesh
{
public:
	unsigned int VBO;
	unsigned int VAO;
	std::vector<Vertex> vertices;
	vec3 translate;
	float rotate;
	Mesh(std::vector<Vertex> vertices, vec3 translate, float rotate);
	~Mesh();
	void setup();
	void drawMesh();
};

