#include "AnimatedMesh.h"

AnimatedMesh::AnimatedMesh(VAO* mesh, Texture* texture, Joint* rootJoint, unsigned int numberOfJoints)
	: model(mesh), texture(texture), rootJoint(rootJoint), numberOfJoints(numberOfJoints)
{ }

AnimatedMesh::~AnimatedMesh()
{
	delete model;
	delete texture;
}

void AnimatedMesh::draw()
{
	std::vector<unsigned int> bindIndices;
	bindIndices.push_back(Mesh::attribVertex);
	bindIndices.push_back(Mesh::attribNormal);
	bindIndices.push_back(Mesh::attribTexCoord);
	bindIndices.push_back(Mesh::attribJointIndices);
	bindIndices.push_back(Mesh::attribWeights);

	this->model->bind(bindIndices);
	glDrawElements(GL_TRIANGLES, model->getIndexCount(), GL_UNSIGNED_INT, 0);
	this->model->unbind(bindIndices);
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

void AnimatedMesh::createFlatTransformArrayFromJoints(Joint* headJoint, glm::mat4* matrices) const
{
	matrices[headJoint->getIndex()] = headJoint->getAnimatedTransform();

	createFlatTransformArrayFromJoints(headJoint->next, matrices);
	createFlatTransformArrayFromJoints(headJoint->child, matrices);
}