#include "VBO.h"

#include "GLIncludes.hpp"

VBO* VBO::create(const int type) 
{
	unsigned int id[1];
	glGenBuffers(1, id);
	return new VBO(id[0], type);
}

VBO::VBO(const unsigned int id, const int type)
	: id(id), type(type)
{ }

VBO::~VBO()
{
	unsigned int uid[1];
	uid[0] = id;
	glDeleteBuffers(1, uid);
}

void VBO::bind()
{
	glBindBuffer(type, id);
}

void VBO::unbind()
{
	glBindBuffer(type, 0);
}

void VBO::storeData(std::vector<float> data)
{
	glBufferData(type, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
}

void VBO::storeData(std::vector<int> data)
{
	glBufferData(type, data.size() * sizeof(int), &data[0], GL_STATIC_DRAW);
}

void VBO::storeData(std::vector<unsigned int> data)
{
	glBufferData(type, data.size() * sizeof(unsigned int), &data[0], GL_STATIC_DRAW);
}