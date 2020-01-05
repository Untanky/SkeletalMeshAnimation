#pragma once
class Joint
{
public:
	Joint(const unsigned int index, const std::string& name, glm::mat4 bindTransform);

	void setParent(Joint parentJoint);

	const glm::mat4 getAnimatedTransform() const;

	void setAnimatedTransform(const glm::mat4 newAnimatedTransform);

	const glm::mat4 getInverseBindTransform() const;

protected:
	const unsigned int index;

	const std::string& name;

	const Joint* next;

	const Joint* child;

	glm::mat4 animatedTransform;

	const glm::mat4 bindTransform;

	const glm::mat4 inverseBindTransform;

	virtual const glm::mat4 calcInverseBindTransform(const glm::mat4 bindTransform) const;
};

