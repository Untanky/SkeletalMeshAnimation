#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "SkinningData.h"

using namespace rapidxml;

class SkinLoader
{
public:
	SkinLoader(xml_node<>* node, unsigned int maxWeights);

	SkinningData extractSkinningData();
};