#pragma once
#include "GameObject.h"
#include "GameEngine.h"
#include "TextReader.h"

class Track : public GameObject
{
private:
	TextReader obj;

	unsigned int texture[2]; // Array of texture indices.
public:

	unsigned int trackTexLoc;
	Track(glm::vec3 position);
	~Track();
	void loadTrackTexture();
	unsigned int vao[2];
	unsigned int buffer[3];
	static enum object { TRACK }; /// VAO ids.
	static enum buffer { TRACK_VERTICES, TRACK_NORMALS }; // VBO ids.
	void setupDrawing();
	void drawScene();
	void update(int deltaTime);
};

