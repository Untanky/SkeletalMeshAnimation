#include "Texture.h"

Texture::~Texture()
{
	glDeleteTextures(1, (unsigned int*)textureId);
}

void Texture::bindToUnit(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, textureId);
}

TextureBuilder* Texture::newTexture(std::string textureFile)
{
	return new TextureBuilder(textureFile);
}

Texture::Texture(int textureId, int size) : textureId(textureId), size(size), type(GL_TEXTURE_2D) { }
Texture::Texture(int textureId, int type, int size) : textureId(textureId), size(size), type(type) { }