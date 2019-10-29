#include "Texture.h"

Texture::Texture(string filepath, int meshID)
{
	this->filepath = filepath;
	
	//this->textureID;
	this->setup();
}

Texture::~Texture()
{
}

void Texture::setup()
{
	image = getbmp(this->filepath);

	glGenTextures(1, &texture);

	// Bind grass image.
	//glActiveTexture(GL_TEXTURE0 + texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->sizeX, image->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//textureLoc = glGetUniformLocation(GraphicsEngine::programId, "tex");
	//glUniform1i(textureLoc, 0);
}