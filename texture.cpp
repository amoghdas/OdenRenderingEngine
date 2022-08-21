#include "texture.h"

Texture::Texture() {
	textureID_ = 0;
	width_ = 0;
	height_ = 0;
	bitDepth_ = 0;
	fileLocation_ = "";
}

Texture::Texture(const char *fileLoc) {
	textureID_ = 0;
	width_ = 0;
	height_ = 0;
	bitDepth_ = 0;
	fileLocation_ = fileLoc;
}

void Texture::loadTexture() {
	unsigned char* texData = stbi_load(fileLocation_, &width_, &height_, &bitDepth_, 0);
	if (!texData) {
		std::cout << "Failed to find: " << fileLocation_ << '\n';
		return;
	}

	glGenTextures(1, &textureID_);
	glBindTexture(GL_TEXTURE_2D, textureID_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);
}

void Texture::useTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID_);
}

void Texture::clearTexture() {
	glDeleteTextures(1, &textureID_);
	textureID_ = 0;
	width_ = 0;
	height_ = 0;
	bitDepth_ = 0;
	fileLocation_ = "";
}

Texture::~Texture() {
	clearTexture();
}