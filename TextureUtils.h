#pragma once

#include "TextureBuilder.h"
#include "TextureData.h"
#include <string>

class TextureUtils
{
public:
	friend class TextureBuilder;

protected:
	static TextureData* decodeTextureFile(std::string file);
	static unsigned int loadTextureToOpenGL(TextureData* data, TextureBuilder* builder);
};

