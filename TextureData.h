#pragma once
class TextureData
{
public:
	TextureData(unsigned char* buffer,  unsigned int width, unsigned int height) 
		: buffer(buffer), width(width), height(height) { }

	unsigned int getWidth() const { return this->width; }

	unsigned int getHeight() const { return this->height; }

	 unsigned char* getBuffer() const { return this->buffer; } 

private:
	unsigned int width;
	unsigned int height;
	unsigned char* buffer;
};

