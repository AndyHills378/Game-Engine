#include "Mesh.h"



Mesh::Mesh(std::vector<Vertex> vertices, vec3 translate, float rotate)
{
	this->vertices = vertices;
	this->setup();
	this->translate = translate;
	this->rotate = rotate;
}

Mesh::~Mesh()
{
}

void Mesh::setup()
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)sizeof(vertices[0].coords));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)(sizeof(vertices[0].coords) + sizeof(vertices[0].normal)));
	glEnableVertexAttribArray(2);
}

void Mesh::drawMesh()
{
	modelMat = mat4(1.0);
	modelMat = glm::translate(modelMat, this->translate);
	modelMat = glm::rotate(modelMat, this->rotate, vec3(0, 1, 0));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size());
}
