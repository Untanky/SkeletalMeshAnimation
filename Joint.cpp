#include "Joint.h"

#include "glm/gtc/matrix_transform.hpp"

Joint::Joint(const unsigned int index, const std::string& name, glm::mat4 bindTransform)
	: index(index), name(name), bindTransform(bindTransform)
{ 
	animatedTransform = glm::mat4(1.0f);
}

void Joint::translate(glm::vec3 translateVector)
{
	glm::mat4 transformMatrix(1.f);
	transformMatrix = glm::translate(transformMatrix, translateVector);

	transform(this, transformMatrix, glm::mat4(1.f), true);
}

void Joint::rotate(glm::vec3 eulerAngles)
{
	glm::mat4 transformMatrix(1.f);
	glm::vec3 translation = glm::vec3(this->jointTransform[3]);

	transformMatrix = glm::translate(transformMatrix, translation);
	transformMatrix = glm::rotate(transformMatrix, glm::radians(eulerAngles.x), glm::vec3(this->jointTransform[0]));
	transformMatrix = glm::rotate(transformMatrix, glm::radians(eulerAngles.y), glm::vec3(this->jointTransform[1]));
	transformMatrix = glm::rotate(transformMatrix, glm::radians(eulerAngles.z), glm::vec3(this->jointTransform[2]));
	transformMatrix = glm::translate(transformMatrix, translation * (-1.f));

	transform(this, transformMatrix, glm::mat4(1.f), true);
}

void Joint::scale(glm::vec3 scaleVector)
{
	glm::mat4 transformMatrix(1.f);
	transformMatrix = glm::scale(transformMatrix, scaleVector);

	transform(this, transformMatrix, glm::mat4(1.f), true);
}

void Joint::transform(glm::mat4 transformMatrix)
{
	transform(this, transformMatrix, glm::mat4(1.f), true);
}

glm::mat4 Joint::getParentTransform(Joint* joint) {
	if (!joint->parent)
		return glm::mat4(1.f);
	
	return glm::mat4(1.0f);
}

void Joint::transform(Joint* joint, glm::mat4 transformMatrix, glm::mat4 parentTransform, bool isRoot)
{
	joint->jointTransform = transformMatrix * joint->jointTransform;

	if (joint->next && !isRoot)
		transform(joint->next, transformMatrix, parentTransform, false);

	if (joint->child)
		transform(joint->child, transformMatrix, joint->jointTransform, false);

	joint->animatedTransform = joint->jointTransform * joint->inverseBindTransform;
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
	this->jointTransform = glm::mat4(bindTransform);
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