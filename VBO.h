#pragma once

#include <vector>

class VBO
{
public:
	static VBO* create(const int type);
	~VBO();

	void bind();

	void unbind();

	void storeData(std::vector<float> data);

	void storeData(std::vector<int> data);

	void storeData(std::vector<unsigned int> data);

private:
	VBO(const unsigned int id, const int type);

	const unsigned int id;

	const int type;
};

