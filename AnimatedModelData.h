#pragma once

#include "MeshData.h"
#include "SkeletonData.h"

class AnimatedModelData
{
public:
	AnimatedModelData(MeshData model, SkeletonData skeleton)
		: mesh(model), joints(skeleton) { }

	inline MeshData getMeshData() const { return this->mesh; }
	inline SkeletonData getJointData() const { return this->joints; }

private:
	const MeshData mesh;
	const SkeletonData joints;
};