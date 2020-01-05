#include "AnimatedMesh.h"

AnimatedMesh::AnimatedMesh(const VAO* mesh, const Texture* texture, const Joint* rootJoint, const unsigned int numberOfJoints)
	: model(mesh), texture(texture), rootJoint(rootJoint), numberOfJoints(numberOfJoints)
{ }

AnimatedMesh::~AnimatedMesh()
{
	delete model;
	delete texture;
}

const std::vector<glm::mat4> AnimatedMesh::getJointTransforms() const
{
	glm::mat4* matrices = (glm::mat4*)malloc(this->numberOfJoints * sizeof(glm::mat4));
	createFlatTransformArrayFromJoints(this->rootJoint, matrices);

	std::vector<glm::mat4> transforms = std::vector<glm::mat4>();
	for (size_t i = 0; i < this->numberOfJoints; i++)
		transforms.push_back(matrices[i]);

	free(matrices);

	return transforms;
}

void AnimatedMesh::createFlatTransformArrayFromJoints(const Joint* headJoint, glm::mat4* matrices) const
{
	matrices[headJoint->getIndex()] = headJoint->getAnimatedTransform();

	createFlatTransformArrayFromJoints(headJoint->next, matrices);
	createFlatTransformArrayFromJoints(headJoint->child, matrices);
}