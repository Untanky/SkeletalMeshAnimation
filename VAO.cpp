#include "VAO.h"

#include "GLIncludes.hpp"

VAO* VAO::create()
{
	unsigned int* id = 0;
	glGenVertexArrays(1, id);
	return new VAO(id[0]);
}

VAO::VAO(const unsigned int id) 
	: id(id) 
{ }

VAO::~VAO()
{
	glDeleteVertexArrays(1, (const unsigned int*)id);
	for each (VBO* vbo in dataVBOs)
	{
		delete vbo;
	}
	delete indexVBO;
}

void VAO::bind()
{
	glBindVertexArray(id);
}

void VAO::bind(std::vector<unsigned int> attributes)
{
	bind();
	for each (unsigned int i in attributes)
	{
		glEnableVertexAttribArray(i);
	}
}

void VAO::unbind()
{
	glBindVertexArray(0);
}

void VAO::unbind(std::vector<unsigned int> attributes)
{
	for each (unsigned int i in attributes)
	{
		glEnableVertexAttribArray(i);
	}
	unbind();
}

void VAO::createIndexBuffer(std::vector<unsigned int> indices)
{
	this->indexVBO = VBO::create(GL_ELEMENT_ARRAY_BUFFER);
	this->indexVBO->bind();
	this->indexVBO->storeData(indices);
	this->indexCount = indices.size();
}

void VAO::createAttribute(int attribute, std::vector<float> data, int attrSize)
{
	VBO* dataVBO = VBO::create(GL_ARRAY_BUFFER);
	dataVBO->bind();
	dataVBO->storeData(data);
	glVertexAttribPointer(attribute, attrSize, GL_FLOAT, GL_FLOAT, attrSize * BYTES_PER_FLOAT, 0);
	dataVBO->unbind();
	dataVBOs.push_back(dataVBO);
}

void VAO::createIntAttribute(int attribute, std::vector<int> data, int attrSize)
{
	VBO* dataVBO = VBO::create(GL_ARRAY_BUFFER);
	dataVBO->bind();
	dataVBO->storeData(data);
	glVertexAttribIPointer(attribute, attrSize, GL_INT, attrSize * BYTES_PET_INT, 0);
	dataVBO->unbind();
	dataVBOs.push_back(dataVBO);
}