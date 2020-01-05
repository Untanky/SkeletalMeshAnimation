#pragma once

#include <vector>

class VBO
{
public:
	static VBO create();
	~VBO();

	unsigned int getIndexCount() const;

	void bind();

	void unbind();

	void storeData(std::vector<float> data);

	void storeData(std::vector<int> data);

private:
	VBO(const unsigned int id);

	const unsigned int id;

	const int type;
};

