#pragma once

#include "glm/glm.hpp"

class MeshData
{
public:
	std::vector<unsigned int> getIndices() const;
	std::vector<float> getVertices() const;
	std::vector<float> getTexCoords() const;
	std::vector<float> getNormals() const;
	std::vector<unsigned int> getJointIds() const;
	std::vector<float> getWeights() const;
};