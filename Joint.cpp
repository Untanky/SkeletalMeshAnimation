#include "Joint.h"

Joint::Joint(const unsigned int index, const std::string& name, glm::mat4 bindTransform)
	: index(index), name(name), bindTransform(bindTransform)
{ }

void Joint::setParent(Joint* parentJoint) 
{
	this->parent = parentJoint;
	if (parentJoint->child == NULL) {
		parentJoint->child = this;
	}
	else {
		Joint* sibling = parentJoint->child;
		while (sibling->next != NULL) sibling = sibling->next;
		sibling->next = this;
		this->previous = sibling;
	}
}

void Joint::calcInverseBindTransform(const glm::mat4 parentTransform)
{
	glm::mat4 bindTransform = parentTransform * this->bindTransform;
	this->inverseBindTransform = glm::inverse(bindTransform);
	next->calcInverseBindTransform(parentTransform);
	child->calcInverseBindTransform(bindTransform);
}