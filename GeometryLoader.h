#pragma once

#include "rapidxml-1.13/rapidxml.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>
#include "MeshData.h"
#include "VertexSkinData.h"
#include "Vertex.h"

using namespace std;
using namespace rapidxml;

class GeometryLoader
{
public:
	GeometryLoader(xml_node<>* node, vector<VertexSkinData> vertexWeights);

	MeshData extractModelData();

	vector<Vertex> vertices;
	vector<glm::vec3> normals;
	vector<glm::vec2> texCoords;
	vector<unsigned int> indices;

private:
	void readRawData();

	void readPositions();
	
	void readNormals();

	void readTexCoords();
	
	void assembleVertices();

	Vertex processVertex(int postionIndex, int normalIndex, int texCoordIndex);

	vector<unsigned int> convertIndicesToArray();

	float convertDataToArray();

	Vertex dealWithAlreadyProcessedVertex(Vertex* perviousVertex, int newTextureIndex, int newNormalIndex);

	void initArrays();

	void removeUnusedVertices();

	xml_node<>* node;

	vector<VertexSkinData> vertexWeights;

	vector<float> verticesArray;
	vector<float> normalsArray;
	vector<float> texCoordsArray;
	vector<unsigned int> indicesArray;
	vector<unsigned int> jointIdsArray;
	vector<float> weightsArray;

	const float PI = 3.1415926f;

	const glm::mat4 CORRECTION = glm::rotate(glm::mat4(1), glm::radians(-90.f), glm::vec3(1.f, 0.f, 0.f));
};
