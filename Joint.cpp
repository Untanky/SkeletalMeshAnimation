#include "Joint.h"

Joint::Joint(const unsigned int index, const std::string& name, glm::mat4 bindTransform)
	: index(index), name(name), bindTransform(bindTransform)
{ 
	animatedTransform = glm::mat4(1.0f);
}

void Joint::transform(glm::mat4 transformMatrix)
{
	transform(this, transformMatrix, true);
}

void Joint::transform(Joint* joint, glm::mat4 transformMatrix, bool isRoot)
{
	glm::mat4 matrix = glm::mat4(1.0f);

	matrix *= transformMatrix;
	joint->animatedTransform *= matrix;

	if (joint->next && !isRoot)
		transform(joint->next, transformMatrix, false);

	if (joint->child)
		transform(joint->child, transformMatrix, false);
}

void Joint::reset() 
{
	reset(this);
}

void Joint::reset(Joint* joint)
{
	joint->animatedTransform = glm::mat4(1.0f);

	if (joint->next)
		reset(joint->next);

	if (joint->child)
		reset(joint->child);
}

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
	if(next)
		next->calcInverseBindTransform(parentTransform);
	if(child)
		child->calcInverseBindTransform(bindTransform);
}

Joint* Joint::getPrevious() {
	return this->previous;
}

Joint* Joint::getNext() {
	return this->next;
}

Joint* Joint::getParent() {
	return this->parent;
}

Joint* Joint::getChild() {
	return this->child;
}