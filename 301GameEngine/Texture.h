#pragma once
#include "GraphicsEngine.h"
#include "Header.h"

class Texture
{
public:
	BitMapFile* image;
	unsigned int texture, textureLoc;
	char textureID;
	string filepath;

	Texture(string filepath, int meshID);
	~Texture();
	void setup();
};

