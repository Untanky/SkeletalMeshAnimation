#pragma once

#include "Node.hpp"

class AnimatedMeshNode : Node
{
public:

	AnimatedMeshNode(AnimatedMesh* mesh, Material material, vec3 position, vec3 rotation, vec3 scale);

	~AnimatedMeshNode();

	AnimatedMesh* getMesh() const;

protected:

	AnimatedMesh* animatedMesh;
};

