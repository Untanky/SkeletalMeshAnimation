#pragma once

#include "TextureUtils.h"
#include <string>

class Texture;

class TextureBuilder
{
public:
	Texture* create();

	TextureBuilder* clampEdges();

	TextureBuilder* normalMipmap();

	TextureBuilder* nearestFiltering();

	TextureBuilder* anisotropic();

	friend class Texture;
	friend class TextureUtils;

protected:
	TextureBuilder(std::string textureFile);

	bool isClampEdges() const {
		return this->_clampEdges;
	}

	bool isMipmap() const {
		return this->_mipmap;
	}

	bool isAnisotropic() const {
		return this->_anisotropic;
	}

	bool isNearest() const {
		return this->_nearest;
	}
private:
	bool _clampEdges = false;
	bool _mipmap = false;
	bool _anisotropic = true;
	bool _nearest = false;

	std::string file;
};

