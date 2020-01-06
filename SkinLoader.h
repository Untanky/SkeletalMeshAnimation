#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "SkinningData.h"
#include "VertexSkinData.h"
#include <string>
#include <vector>

using namespace rapidxml;

class SkinLoader
{
public:
	SkinLoader(xml_node<>* node, unsigned int maxWeights);

	SkinningData extractSkinningData();
	
private:
	std::vector<std::string> loadJointList();

	std::vector<float> loadWeights();

	std::vector<int> getEffectiveJointsCounts(xml_node<>* weightsDataNode);

	std::vector<VertexSkinData> getSkinData(xml_node<>* weightsDataNode, std::vector<int> counts, std::vector<float> weights);

	const xml_node<>* skinningData;
	const unsigned int maxWeights;
};