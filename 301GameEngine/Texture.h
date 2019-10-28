#pragma once
#include "GraphicsEngine.h"
#include "Header.h"

class Texture
{
public:
	BitMapFile* image[2];
	unsigned int texture[1], textureLoc;
	int textureID;
	string filepath;

	Texture(string filepath, int meshID);
	~Texture();
	void setup();
};

