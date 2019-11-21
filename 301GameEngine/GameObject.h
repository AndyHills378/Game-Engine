#pragma once

#include "Header.h"
#include "Mesh.h"
#include "Texture.h"
#include "GraphicsEngine.h"

/*struct Colour {
	float r, g, b;
};*/

class GameObject
{
protected:
	Mesh* mesh;
	Texture* texture;
	//TextReader obj;
public:
	int objectID;
	char* filename;
	vec3 position, scale, rotateVec;
	std::string textureLoc;
	float rotate;
	bool objectToFollow;
	glm::vec3 startHeading = glm::vec3(0.0, 0.0, -1.0);
	glm::vec3 heading = startHeading;
	GameObject(char* filename, char* luaID, int objectID, bool objectToFollow);
	~GameObject();

	void setupObject();

	void drawObject();

};
