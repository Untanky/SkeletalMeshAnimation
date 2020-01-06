#pragma once

#include "AnimatedModelData.h"
#include <string>

class ColladaLoader
{
public:
	static AnimatedModelData loadColladaModel(const std::string& meshFilepath, const unsigned int maxWeights);
};

