#pragma once

#include <iostream>
#include <GL/glew.h>
#include "stb_image.h"

class Texture
{
public:
	Texture();
	Texture(const char *fileLoc);

	void loadTexture();
	void useTexture();
	void clearTexture();

	~Texture();

private:
	GLuint textureID_;
	int width_, height_, bitDepth_;

	const char* fileLocation_;
};

