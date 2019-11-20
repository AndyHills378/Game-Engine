#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, vec3 position, float rotate, glm::vec3 rotateVec, int meshID)
{
	this->vertices = vertices;
	this->position = position;
	this->rotate = rotate;
	this->meshID = meshID;
	this->model = false;
	this->scale = vec3(1.0f);
	this->rotateVec = rotateVec;
	this->setup();
}

Mesh::Mesh(char* filename, int meshID, glm::vec3 position, float rotate, glm::vec3 scale)
{
	obj.LoadModel(filename);
	this->position = position;
	this->meshID = meshID;
	this->model = true;
	this->scale = scale;
	this->rotate = rotate;
	this->rotateVec = vec3(0.0f, 1.0f, 0.0f);
	this->modelSetup();
}

Mesh::~Mesh()
{
}

void Mesh::modelSetup()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * obj.numFaces * 3, obj.verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(Vertex::coords));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vertex::coords) + sizeof(Vertex::normal)));
	glEnableVertexAttribArray(2);
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
	modelMat = glm::translate(modelMat, this->position);
	modelMat = glm::rotate(modelMat, this->rotate, this->rotateVec);
	modelMat = glm::scale(modelMat, this->scale);
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));
	//glBindVertexArray(VAO);

	//glActiveTexture(GL_TEXTURE0 + meshID);
	glBindTexture(GL_TEXTURE_2D, this->meshID);
	if (this->model) { glDrawArrays(GL_TRIANGLES, 0, obj.numFaces * 3); }

	else { glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size()); }
}
