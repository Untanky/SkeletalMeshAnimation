#include "TextureBuilder.h"

#include "Texture.h"
#include "TextureData.h"

Texture* TextureBuilder::create()
{
	TextureData* textureData = TextureUtils::decodeTextureFile(file);
	int textureId = TextureUtils::loadTextureToOpenGL(textureData, this);
	return new Texture(textureId, textureData->getWidth());
}

TextureBuilder* TextureBuilder::clampEdges()
{
	this->_clampEdges = true;
	return this;
}

TextureBuilder* TextureBuilder::normalMipmap()
{
	this->_mipmap = true;
	this->_anisotropic = false;
	return this;
}

TextureBuilder* TextureBuilder::nearestFiltering()
{
	this->_mipmap = false;
	this->_anisotropic = false;
	this->_nearest = true;
	return this;
}

TextureBuilder* TextureBuilder::anisotropic()
{
	this->_mipmap = true;
	this->_anisotropic = true;
	return this;
}

TextureBuilder::TextureBuilder(std::string textureFile)
	: file(textureFile)
{

}