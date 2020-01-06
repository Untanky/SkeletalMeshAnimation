#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "MeshData.h"

using namespace rapidxml;

class GeometryLoader
{
public:
	GeometryLoader(xml_node<>* node, unsigned int maxWeights);

	MeshData extractModelData();
};
