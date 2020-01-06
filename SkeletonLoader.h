#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "SkeletonData.h"

using namespace rapidxml;

class SkeletonLoader
{
public:
	SkeletonLoader(xml_node<>* node, unsigned int maxWeights);

	SkeletonData extractSkeletonData();
};