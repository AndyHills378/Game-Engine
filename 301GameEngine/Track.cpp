#include "Track.h"

Track::Track(glm::vec3 position) : GameObject(position)
{
	char filename[] = "TrackTest.obj";
	obj.LoadModel(filename);
}

Track::~Track()
{
}

void Track::loadTrackTexture()
{
	// Local storage for bmp image data.
	BitMapFile *image[5];

	// Load the textures.
	image[0] = getbmp("./Textures/asteroid.bmp");

	// Bind grass image.
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->sizeX, image[0]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	trackTexLoc = glGetUniformLocation(GraphicsEngine::programId, "trackTex");
	glUniform1i(trackTexLoc, 3);
}

void Track::setupDrawing()
{
	glGenTextures(2, texture);
	loadTrackTexture();

	glGenVertexArrays(1, vao);
	glGenBuffers(1, buffer);

	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * obj.numFaces * 3, obj.verts, GL_STATIC_DRAW);
	glVertexAttribPointer(10, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);  //layout(location=4) in vec4 fieldCoords;
	glEnableVertexAttribArray(10);
	glVertexAttribPointer(11, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vertex::coords)+sizeof(Vertex::normal)));  //layout(location=4) in vec4 fieldCoords;
	glEnableVertexAttribArray(11);
}

void Track::drawScene()
{
	
	mat4 modelMat = mat4(1.0);
	modelMat = translate(modelMat, this->position);
	//modelMat = rotate(modelMat, glm::radians(-90.0f), glm::vec3(0, 1, 0));
	modelMat = rotate(modelMat, -glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMat = scale(modelMat, vec3(100, 100, 1));
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));  //send to the shader
	glUniform1ui(glGetUniformLocation(GraphicsEngine::programId, "object"), 5);
	glBindVertexArray(vao[0]);
	
	glDrawArrays(GL_TRIANGLES, 0, obj.numFaces * 3);
}

void Track::update(int deltaTime)
{
}
