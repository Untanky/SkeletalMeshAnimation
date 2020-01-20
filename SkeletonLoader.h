#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "SkeletonData.h"
#include <string>

#include "glm/gtc/matrix_transform.hpp"

using namespace std;
using namespace rapidxml;

constexpr int BUFFER_SIZE = 16;

constexpr float PI = 3.1415926f;

class SkeletonLoader
{
public:
	SkeletonLoader(xml_node<>* node, vector<string> boneOrder);

	SkeletonData extractSkeletonData();

private:
	JointData* loadJointData(xml_node<>* jointNode, bool isRoot);

	JointData* extractMainData(xml_node<>* jointNode, bool isRoot);

	glm::mat4 convertData(vector<string>);

	xml_node<>* armatureData;

	vector<string> boneOrder;

	int jointCount = 0;

	const glm::mat4 CORRECTION = glm::rotate(glm::mat4(1), PI / 360.f * 90.f, glm::vec3(1.f, 0.f, 0.f));
};