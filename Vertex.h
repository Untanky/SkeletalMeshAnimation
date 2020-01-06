#pragma once

#include "VertexSkinData.h"
#include "glm/glm.hpp"
#include <vector>

constexpr int NO_INDEX = -1;

class Vertex
{
public:
	Vertex(int index, glm::vec3 position, VertexSkinData weightsData)
		: index(index), position(position), weightsData(weightsData), length(3)
	{}

	VertexSkinData getWeightsData() const { return this->weightsData; }

	void addTangent(glm::vec3 tangent) { this->tangents.push_back(tangent); }

	void avereageTangent()
	{
		if (tangents.empty())
			return;
		for each (glm::vec3 tangent in tangents)
		{
			averagedTangent = averagedTangent + tangent;
		}
		glm::normalize(averagedTangent);
	}

	glm::vec3 getAverageTangent() const { return this->averagedTangent; }

	int getIndex() const { return this->index; }

	float getLength() const { return this->length; }

	bool isSet() const { return this->textureIndex != NO_INDEX && this->normalIndex != NO_INDEX; }

	bool hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther) const { return this->textureIndex == textureIndexOther && this->normalIndex == normalIndexOther; }

	glm::vec3 getPosition() const { return this->position; }

	int getTextureIndex() const { return this->textureIndex; }

	void setTextureIndex(int textureIndex) { this->textureIndex = textureIndex; }

	int getNormalIndex() const { return this->normalIndex; }

	void setNormalIndex(int normalIndex) { this->normalIndex = normalIndex; }

	Vertex* getDuplicateVertex() const { return this->duplicateVertex; }

	void setDuplicateVertex(Vertex* duplicateVertex) { this->duplicateVertex = duplicateVertex; }

private:
	glm::vec3 position;
	int textureIndex = NO_INDEX;
	int normalIndex = NO_INDEX;
	Vertex* duplicateVertex = nullptr;
	int index;
	float length;
	vector<glm::vec3> tangents;
	glm::vec3 averagedTangent;
	VertexSkinData weightsData;
};