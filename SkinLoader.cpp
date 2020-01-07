#include "SkinLoader.h"

#include "rapidxml-1.13/rapidxml_helper.hpp"

SkinLoader::SkinLoader(xml_node<>* node, unsigned int maxWeights)
	: skinningData(node->first_node("controller\0")->first_node("skin\0")), maxWeights(maxWeights)
{ 

}

SkinningData SkinLoader::extractSkinningData()
{
	std::vector<std::string> jointsList = loadJointList();
	std::vector<float> weights = loadWeights();

	xml_node<>* weightsDataNode = skinningData->first_node("vertex_weights\0");
	std::vector<int> effectorJointsCounts = getEffectiveJointsCounts(weightsDataNode);
	std::vector<VertexSkinData> vertexWeights = getSkinData(weightsDataNode, effectorJointsCounts, weights);
	return SkinningData(jointsList, vertexWeights);
}

std::vector<std::string> SkinLoader::loadJointList()
{
	xml_node<>* weightNode = skinningData->first_node("vertex_weights\0");

	std::string jointDataId = getChildWithAttribute(weightNode, "input\0", "semantic\0", "JOINT\0")->first_attribute("source\0")->value();
	jointDataId = jointDataId.substr(1);

	xml_node<>* jointsNode = getChildWithAttribute(skinningData, "source\0", "id\0", jointDataId + "\0")->first_node("Name_array\0");
	string names = jointsNode->value();

	vector<string> joints;
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = names.find(delimiter)) != std::string::npos) {
		token = names.substr(0, pos);
		joints.push_back(token);
		names.erase(0, pos + delimiter.length());
	}

	return joints;
}

std::vector<float> SkinLoader::loadWeights()
{
	xml_node<>* weightNode = skinningData->first_node("vertex_weights\0");

	std::string weightsDataId = getChildWithAttribute(weightNode, "input\0", "semantic\0", "WEIGHT\0")->first_attribute("source\0")->value();
	weightsDataId = weightsDataId.substr(1);

	xml_node<>* weightsNode = getChildWithAttribute(skinningData, "source\0", "id\0", weightsDataId + "\0")->first_node("float_array\0");
	string rawData = weightsNode->value();

	vector<float> joints;
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = rawData.find(delimiter)) != std::string::npos) {
		token = rawData.substr(0, pos);
		joints.push_back(std::stof(token));
		rawData.erase(0, pos + delimiter.length());
	}
	joints.push_back(std::stof(rawData));

	return joints;
}

std::vector<int> SkinLoader::getEffectiveJointsCounts(xml_node<>* weightsDataNode)
{
	xml_node<>* weightsNode = weightsDataNode->first_node("vcount\0");
	string rawData = weightsNode->value();

	vector<int> counts;
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = rawData.find(delimiter)) != std::string::npos) {
		token = rawData.substr(0, pos);
		counts.push_back(std::stoi(token));
		rawData.erase(0, pos + delimiter.length());
	}

	return counts;
}

std::vector<VertexSkinData> SkinLoader::getSkinData(xml_node<>* weightsDataNode, std::vector<int> counts, std::vector<float> weights)
{
	xml_node<>* weightsNode = weightsDataNode->first_node("v\0");
	string rawData = weightsNode->value();
	vector<string> rawDataList;
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = rawData.find(delimiter)) != std::string::npos) {
		token = rawData.substr(0, pos);
		rawDataList.push_back(token);
		rawData.erase(0, pos + delimiter.length());
	}
	rawDataList.push_back(rawData);

	int pointer = 0;
	vector<VertexSkinData> skinningData;
	for (int j = 0; j < counts.size(); j++)
	{
		int count = counts[j];
		VertexSkinData skinData = VertexSkinData();
		for (int i = 0; i < count; i++)
		{
			if (pointer >= 2780) {
				pointer = pointer;
				j = j;
			}
			int jointId = std::stoi(rawDataList[pointer++]);
			int weightId = std::stoi(rawDataList[pointer++]);
			skinData.addJointEffect(jointId, weights[weightId]);
		}
		skinData.limitJointNumber(maxWeights);
		skinningData.push_back(skinData);
	}

	return skinningData;
}