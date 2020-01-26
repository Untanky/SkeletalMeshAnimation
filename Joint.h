#pragma once

#include <string>

#include "glm/glm.hpp"

class Joint
{
public:
	Joint(const unsigned int index, const std::string& name, glm::mat4 bindTransform);

	void transform(glm::mat4 transformMatrix);

	void reset();

	void setParent(Joint* parentJoint);

	inline const glm::mat4 getAnimatedTransform() const { return this->animatedTransform; }

	inline void setAnimatedTransform(const glm::mat4 newAnimatedTransform) { this->animatedTransform = newAnimatedTransform; }

	const glm::mat4 getInverseBindTransform() const { return this->inverseBindTransform; }

	inline unsigned int getIndex() const { return this->index; }

	inline const std::string& getName() const { return this->name; }

	Joint* getPrevious();
	Joint* getNext();
	Joint* getParent();
	Joint* getChild();

	friend class AnimatedMesh;

protected:
	const unsigned int index;

	const std::string& name;

	Joint* previous = 0;
	Joint* next = 0;
	Joint* parent = 0;
	Joint* child = 0;

	glm::mat4 animatedTransform;

	const glm::mat4 bindTransform;

	glm::mat4 inverseBindTransform;

	glm::mat4 jointTransform;

	void calcInverseBindTransform(const glm::mat4 bindTransform);

	static glm::mat4 getParentTransform(Joint* joint);

	static void transform(Joint* joint, glm::mat4 transformMatrix, glm::mat4 parentTransform, bool isRoot);

	static void reset(Joint* joint);
};

