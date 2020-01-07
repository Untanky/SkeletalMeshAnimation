#include "SkeletonLoader.h"

#include "glm/gtc/type_ptr.hpp"
#include "rapidxml-1.13/rapidxml_helper.hpp"

SkeletonLoader::SkeletonLoader(xml_node<>* node, vector<string> boneOrder)
	: armatureData(getChildWithAttribute(node->first_node("visual_scene\0"), "node\0", "id\0", "Armature\0")), boneOrder(boneOrder)
{ }

SkeletonData SkeletonLoader::extractSkeletonData()
{
	xml_node<>* headNode = armatureData->first_node("node\0");
	JointData* headJoint = loadJointData(headNode, true);
	return SkeletonData(jointCount, headJoint);
}

JointData* SkeletonLoader::loadJointData(xml_node<>* jointNode, bool isRoot)
{
	JointData* joint = extractMainData(jointNode, isRoot);

	xml_node<>* node = jointNode->first_node("node\0");
	while (node)
	{
		joint->addChild(loadJointData(node, false));
		node = node->next_sibling("node\0");
	}
	
	return joint;
}

JointData* SkeletonLoader::extractMainData(xml_node<>* jointNode, bool isRoot)
{
	string nameId = jointNode->first_attribute("id\0")->value();
	int index = find(boneOrder.begin(), boneOrder.end(), nameId) - boneOrder.begin();
	string rawData = jointNode->first_node("matrix\0")->value();
	vector<string> matrixData;
	string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = rawData.find(delimiter)) != std::string::npos) {
		token = rawData.substr(0, pos);
		matrixData.push_back(token);
		rawData.erase(0, pos + delimiter.length());
	}
	matrixData.push_back(rawData);

	glm::mat4 matrix = glm::make_mat4(convertData(matrixData));
	matrix = glm::transpose(matrix);

	jointCount++;
	return new JointData(index, nameId, matrix);
}

float* SkeletonLoader::convertData(vector<string> rawData)
{
	float matrixData[16];

	for (int i = 0; i < 16; i++)
	{
		matrixData[i] = stof(rawData[i]);
	}

	return matrixData;
}