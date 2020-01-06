#pragma once

#include "glm/glm.hpp"
#include <vector>

class JointData 
{
public:
	const unsigned int index;

	const std::string& name;

	const glm::mat4 bindTransform;

	Joint* parent;

	const std::vector<JointData> children;
};