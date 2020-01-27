#include "TextureUtils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "GLIncludes.hpp"

TextureData* TextureUtils::decodeTextureFile(std::string file)
{
	int width = 0;
	int height = 0;
	int nrChannels;
	unsigned char* data = stbi_load(file.data(), &width, &height, &nrChannels, 0);

	return new TextureData(data, width, height);
}

unsigned int TextureUtils::loadTextureToOpenGL(TextureData* data, TextureBuilder* builder) 
{
	unsigned int texId;
	glGenTextures(1, &texId);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texId);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->getWidth(), data->getHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, data->getBuffer());

	if (builder->isMipmap()) {
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		if (builder->isAnisotropic() && GL_EXT_texture_filter_anisotropic) {
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.f);
		}
	}
	else if (builder->isNearest()) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else if (builder->isAnisotropic()) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	if (builder->isClampEdges()) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	return texId;
}