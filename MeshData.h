#pragma once

#include "glm/glm.hpp"
#include <vector>

constexpr int DIMENSIONS = 3;

class MeshData
{
public:
	MeshData(
		const std::vector<unsigned int> indices,
		const std::vector<float> vertices,
		const std::vector<float> texCoords,
		const std::vector<float> normals,
		const std::vector<unsigned int> jointIds,
		const std::vector<float> weights
	) :
		indices(indices),
		vertices(vertices),
		texCoords(texCoords),
		normals(normals),
		jointIds(jointIds),
		weights(weights)
	{ }


	inline std::vector<unsigned int> getIndices() const { return this->indices; }
	inline std::vector<float> getVertices() const { return this->vertices; }
	inline std::vector<float> getTexCoords() const { return this->texCoords; }
	inline std::vector<float> getNormals() const { return this->normals; }
	inline std::vector<unsigned int> getJointIds() const { return this->jointIds; }
	inline std::vector<float> getWeights() const { return this->weights; }
	inline int getVertexCount() const { return (int)vertices.size() / DIMENSIONS; }

private:
	const std::vector<unsigned int> indices; 
	const std::vector<float> vertices;
	const std::vector<float> texCoords;
	const std::vector<float> normals;
	const std::vector<unsigned int> jointIds;
	const std::vector<float> weights;
};