#pragma once
#include "GraphicsEngine.h"

class Texture
{
public:
	BitMapFile* image[1];
	unsigned int texture[1];
	unsigned int textureLoc;
	string filepath;
	Texture(string filepath);
	~Texture();
	void setup();
};

