#pragma once

#include "Mesh.h"
#include "Joint.h"
#include "VAO.h"
#include "Texture.h"
#include <vector>

class AnimatedMesh : Mesh
{
public:
	AnimatedMesh(VAO* mesh, Texture* texture, Joint* rootJoint, unsigned int numberOfJoints);
	~AnimatedMesh();

	virtual void draw() override;

	// returns the model 
	VAO* getModel() const { return this->model; };

	// returns the texture
	Texture* getTexture() const { return this->texture; };

	// returns the joints
	Joint* getRootJoint() const { return this->rootJoint; };

	// returns the transforms of the joints
	const std::vector<glm::mat4> getJointTransforms() const;

protected:
	// the root of the joint hierachy
	Joint* rootJoint;

	// the number of joints
	const unsigned int numberOfJoints;

	// the skin of the animated mesh
	VAO* model;

	// the texture of the mesh
	Texture* texture;

private:
	// create a flat array of transforms from the joints
	void createFlatTransformArrayFromJoints(Joint* headJoint, glm::mat4* matrices) const;
};

