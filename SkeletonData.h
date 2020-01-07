#pragma once

#include "JointData.h"

class SkeletonData
{
public:
	const int jointCount;
	JointData* headJoint;

	SkeletonData(const int jointCount, JointData* headJoint)
		: jointCount(jointCount), headJoint(headJoint)
	{ }
};