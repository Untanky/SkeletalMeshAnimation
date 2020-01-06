#pragma once

#include "AnimatedModelData.h"

class ColladaLoader
{
public:
	static AnimatedModelData loadColladaModel(const std::string& meshFilepath, const unsigned int maxWeights);
};

