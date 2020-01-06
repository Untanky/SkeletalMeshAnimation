#pragma once

#include "JointData.h"

class SkeletonData
{
public:
	const int jointCount;
	const JointData headJoint;

	SkeletonData(const int jointCount, const JointData headJoint)
		: jointCount(jointCount), headJoint(headJoint)
	{ }
};