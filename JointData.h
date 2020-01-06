#pragma once

#include "Joint.h"
#include "glm/glm.hpp"
#include <vector>

class JointData 
{
public:
	const unsigned int index;

	const std::string& name;

	const glm::mat4 bindTransform;

	Joint* parent;

	std::vector<JointData> children;

	JointData(unsigned int index, std::string& name, glm::mat4 bindTransfrom)
		: index(index), name(name), bindTransform(bindTransform) { }

	inline void addChild(JointData child)
	{
		children.push_back(child);
	}
};