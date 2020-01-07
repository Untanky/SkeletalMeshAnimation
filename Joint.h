#pragma once

#include <string>

#include "glm/glm.hpp"

class Joint
{
public:
	Joint(const unsigned int index, const std::string& name, glm::mat4 bindTransform);

	void setParent(Joint* parentJoint);

	inline const glm::mat4 getAnimatedTransform() const { return this->animatedTransform; }

	inline void setAnimatedTransform(const glm::mat4 newAnimatedTransform) { this->animatedTransform = newAnimatedTransform; }

	const glm::mat4 getInverseBindTransform() const { return this->inverseBindTransform; }

	inline unsigned int getIndex() const { return this->index; }

	inline const std::string& getName() const { return this->name; }

	friend class AnimatedMesh;

protected:
	const unsigned int index;

	const std::string& name;

	Joint* previous;
	Joint* next;
	Joint* parent;
	Joint* child;

	glm::mat4 animatedTransform;

	const glm::mat4 bindTransform;

	glm::mat4 inverseBindTransform;

	void calcInverseBindTransform(const glm::mat4 bindTransform);
};

