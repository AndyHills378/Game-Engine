#pragma once
#include "GraphicsEngine.h"
#include <vector>
#include "Texture.h"
class Mesh
{
public:
	unsigned int VBO;
	unsigned int VAO;
	std::vector<Vertex> vertices;
	vec3 translate;
	float rotate;
	int meshID;
	Mesh(std::vector<Vertex> vertices, vec3 translate, float rotate, int meshID);
	~Mesh();
	void setup();
	void drawMesh();
};

