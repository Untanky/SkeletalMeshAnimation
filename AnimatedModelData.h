#pragma once

#include "MeshData.h"
#include "SkeletonData.h"

class AnimatedModelData
{
public:
	MeshData getMeshData() const;
	SkeletonData getJointData() const;
};