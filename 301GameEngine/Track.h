#pragma once
#include "GameObject.h"
#include "GameEngine.h"
#include "TextReader.h"
#include "Header.h"

class Track : public GameObject
{
private:
	TextReader obj;

	//unsigned int texture[2]; // Array of texture indices.
public:

	Track(glm::vec3 position);
	~Track();
	void loadTrackTexture();

	void setupDrawing();
	void drawScene();
	void update(int deltaTime);
};

