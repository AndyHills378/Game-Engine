#pragma once
#include "Header.h"
#include "getbmp.h"

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
	void setupCubeMap();
};

