#pragma once

#include "Joint.h"
#include "VAO.h"
#include "Texture.hpp"
#include <vector>

class AnimatedMesh
{
public:
	AnimatedMesh(const VAO* mesh, const Texture* texture, const Joint* rootJoint, const unsigned int numberOfJoints);
	~AnimatedMesh();

	// returns the model 
	inline const VAO* getModel() const { return this->model; }

	// returns the texture
	inline const Texture* getTexture() const { return this->texture; }

	// returns the joints
	inline const Joint* getRootJoint() const { return this->rootJoint; }

	// returns the transforms of the joints
	const std::vector<glm::mat4> getJointTransforms() const;

protected:
	// the root of the joint hierachy
	const Joint* rootJoint;

	// the number of joints
	const unsigned int numberOfJoints;

	// the skin of the animated mesh
	const VAO* model;

	// the texture of the mesh
	const Texture* texture;

private:
	// create a flat array of transforms from the joints
	void createFlatTransformArrayFromJoints(const Joint* headJoint, glm::mat4* matrices) const;
};

