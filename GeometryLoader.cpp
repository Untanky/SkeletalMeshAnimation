#include "GeometryLoader.h"

#include <string>
#include "rapidxml-1.13/rapidxml_helper.hpp"
#include "glm/gtc/matrix_transform.hpp"

GeometryLoader::GeometryLoader(xml_node<>* node, vector<VertexSkinData> vertexWeights)
	: vertexWeights(vertexWeights), node(node)
{ }

MeshData GeometryLoader::extractModelData()
{
	readRawData();
	assembleVertices();
	removeUnusedVertices();
	initArrays();
	convertDataToArray();
	convertIndicesToArray();
	return MeshData(indicesArray, verticesArray, texCoordsArray, normalsArray, jointIdsArray, weightsArray);
}

void GeometryLoader::readRawData()
{
	readPositions();
	readNormals();
	readTexCoords();
}

void GeometryLoader::readPositions()
{
	string positionId = node->first_node("vertices\0")->first_node("input\0")->first_attribute("source\0")->value();
	positionId.substr(1);
	xml_node<>* positionData = getChildWithAttribute(node, "source\0", "id\0", positionId)->first_node("float_array\0");
	int count = stoi(positionData->first_attribute("count\0")->value());
	string posData = positionData->value();
	vector<string> posDataList;
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = posData.find(delimiter)) != std::string::npos) {
		token = posData.substr(0, pos);
		posDataList.push_back(token);
		posData.erase(0, pos + delimiter.length());
	}

	for (int i = 0; i < count/3; i++)
	{
		float x = stof(posDataList[i * 3]);
		float y = stof(posDataList[i * 3 + 1]);
		float z = stof(posDataList[i * 3 + 2]);
		glm::vec4 pos = glm::vec4(x, y, z, 0.f);
		pos = CORRECTION * pos;
		vertices.push_back(Vertex(vertices.size(), glm::vec3(pos.x, pos.y, pos.z), vertexWeights[vertices.size()]));
	}
}

void GeometryLoader::readNormals()
{
	string normalId = getChildWithAttribute(node->first_node("polylist\0"), "input\0", "semantic\0", "NORMAL")->first_attribute("source\0")->value();
	normalId.substr(1);
	xml_node<>* normalData = getChildWithAttribute(node, "source\0", "id\0", normalId)->first_node("float_array\0");
	int count = stoi(normalData->first_attribute("count\0")->value());
	string normData = normalData->value();
	vector<string> normDataList;
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = normData.find(delimiter)) != std::string::npos) {
		token = normData.substr(0, pos);
		normDataList.push_back(token);
		normData.erase(0, pos + delimiter.length());
	}

	for (int i = 0; i < count / 3; i++)
	{
		float x = stof(normDataList[i * 3]);
		float y = stof(normDataList[i * 3 + 1]);
		float z = stof(normDataList[i * 3 + 2]);
		glm::vec4 norm = glm::vec4(x, y, z, 0.f);
		norm = CORRECTION * norm;
		normals.push_back(norm);
	}
}

void GeometryLoader::readTexCoords()
{
	string texCoordId = getChildWithAttribute(node->first_node("polylist\0"), "input\0", "semantic\0", "TEXCOORD")->first_attribute("source\0")->value();
	texCoordId.substr(1);
	xml_node<>* texCoordsData = getChildWithAttribute(node, "source\0", "id\0", texCoordId)->first_node("float_array\0");
	int count = stoi(texCoordsData->first_attribute("count\0")->value());
	string texCoordData = texCoordsData->value();
	vector<string> texCoordDataList;
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = texCoordData.find(delimiter)) != std::string::npos) {
		token = texCoordData.substr(0, pos);
		texCoordDataList.push_back(token);
		texCoordData.erase(0, pos + delimiter.length());
	}

	for (int i = 0; i < count / 3; i++)
	{
		float s = stof(texCoordDataList[i * 3]);
		float t = stof(texCoordDataList[i * 3 + 1]);
		glm::vec2 texCoord = glm::vec2(s, t);
		texCoords.push_back(texCoord);
	}
}

void GeometryLoader::assembleVertices()
{
	xml_node<>* poly = node->first_node("polylist\0");
	int typeCount = stoi(poly->first_attribute("count\0")->value());
	string indexRawData = poly->value();
	vector<string> indexData;
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = indexRawData.find(delimiter)) != std::string::npos) {
		token = indexRawData.substr(0, pos);
		indexData.push_back(token);
		indexRawData.erase(0, pos + delimiter.length());
	}

	for (int i = 0; i < indexData.size() / typeCount; i++)
	{
		int positionIndex = stoi(indexData[i * typeCount]);
		int normalIndex = stoi(indexData[i * typeCount + 1]);
		int texCoordIndex = stoi(indexData[i * typeCount + 2]);
		processVertex(positionIndex, normalIndex, texCoordIndex);
	}
}

Vertex GeometryLoader::processVertex(int postionIndex, int normalIndex, int texCoordIndex)
{
	Vertex currentVertex = vertices[postionIndex];
	if (!currentVertex.isSet())
	{
		currentVertex.setTextureIndex(texCoordIndex);
		currentVertex.setNormalIndex(texCoordIndex);
		indices.push_back(postionIndex);
		return currentVertex;
	}
	else
	{
		return dealWithAlreadyProcessedVertex(currentVertex, texCoordIndex, normalIndex);
	}
}

vector<unsigned int> GeometryLoader::convertIndicesToArray()
{
	indicesArray = vector<unsigned int>();
	for (int i = 0; i < indices.size(); i++)
	{
		indicesArray.push_back(indices[i]);
	}
	return indicesArray;
}

float GeometryLoader::convertDataToArray()
{
	float furthestPoint = 0;

	for (int i = 0; i < vertices.size(); i++)
	{
		Vertex currentVertex = vertices[i];
		if (currentVertex.getLength() > furthestPoint)
			furthestPoint = currentVertex.getLength();
		glm::vec3 position = currentVertex.getPosition();
		glm::vec3 normal = normals[currentVertex.getNormalIndex()];
		glm::vec2 texCoord = texCoords[currentVertex.getTextureIndex()];
		verticesArray.push_back(position.x);
		verticesArray.push_back(position.y);
		verticesArray.push_back(position.z);
		texCoordsArray.push_back(texCoord.x);
		texCoordsArray.push_back(texCoord.y);
		normalsArray.push_back(normal.x);
		normalsArray.push_back(normal.y);
		normalsArray.push_back(normal.z);
		VertexSkinData weights = currentVertex.getWeightsData();
		jointIdsArray.push_back(weights.jointIds[0]);
		jointIdsArray.push_back(weights.jointIds[1]);
		jointIdsArray.push_back(weights.jointIds[2]);
		weightsArray.push_back(weights.weights[0]);
		weightsArray.push_back(weights.weights[1]);
		weightsArray.push_back(weights.weights[2]);
	}

	return furthestPoint;
}

Vertex GeometryLoader::dealWithAlreadyProcessedVertex(Vertex previousVertex, int newTextureIndex, int newNormalIndex)
{
	if (previousVertex.hasSameTextureAndNormal(newTextureIndex, newNormalIndex))
	{
		indices.push_back(previousVertex.getIndex());
		return previousVertex;
	}
	else
	{
		Vertex* anotherVertex = previousVertex.getDuplicateVertex();
		if (anotherVertex)
		{
			return dealWithAlreadyProcessedVertex(*anotherVertex, newTextureIndex, newNormalIndex);
		}
		else
		{
			Vertex duplicateVertex = Vertex(vertices.size(), previousVertex.getPosition(), previousVertex.getWeightsData());
			duplicateVertex.setTextureIndex(newTextureIndex);
			duplicateVertex.setNormalIndex(newNormalIndex);
			previousVertex.setDuplicateVertex(&duplicateVertex);
			vertices.push_back(duplicateVertex);
			indices.push_back(duplicateVertex.getIndex());
			return duplicateVertex;
		}
	}
}

void GeometryLoader::initArrays()
{
	// nothing to do
}

void GeometryLoader::removeUnusedVertices()
{
	for each (Vertex vertex in vertices)
	{
		vertex.averageTangents();
		if (!vertex.isSet())
		{
			vertex.setTextureIndex(0);
			vertex.setNormalIndex(0);
		}
	}
}