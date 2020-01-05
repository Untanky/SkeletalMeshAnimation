#pragma once

#include "VBO.h"
#include <vector>

constexpr auto BYTES_PER_FLOAT = 4;
constexpr auto BYTES_PET_INT = 4;

class VAO
{
public :

	static VAO* create();
	~VAO();

	const unsigned int id;

	inline unsigned int getIndexCount() const { return this->indexCount; }

	void bind(std::vector<unsigned int> attributes);

	void unbind(std::vector<unsigned int> attributes);

	void createIndexBuffer(std::vector<unsigned int> indices);

	void createAttribute(int attribute, std::vector<float> data, int attrSize);

	void createIntAttribute(int attribute, std::vector<int> data, int attrSize);

private:
	VAO(const unsigned int id);

	std::vector<VBO*> dataVBOs;

	VBO* indexVBO;

	unsigned int indexCount;

	void bind();

	void unbind();
};

