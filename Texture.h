#pragma once

#include "GLIncludes.hpp"
#include "TextureBuilder.h"
#include <string>

class Texture 
{
public:
	const unsigned int textureId;
	const unsigned int size;

	~Texture();

	void bindToUnit(unsigned int unit);

	friend class TextureBuilder;

	static TextureBuilder* newTexture(std::string textureFile);

protected:
	Texture(int textureId, int size);
	Texture(int textureId, int type, int size);

private:
	const int type;
};