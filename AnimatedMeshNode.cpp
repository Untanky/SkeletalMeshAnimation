#include "AnimatedMeshNode.h"

AnimatedMeshNode::AnimatedMeshNode(AnimatedMesh* mesh, Material material, vec3 position, vec3 rotation, vec3 scale)
	: Node((Mesh*)mesh, material, 
		position.x, position.y, position.z, 
		scale.x, scale.y, scale.z, 
		0, 0, 0, 
		rotation.x, rotation.y, rotation.z),
	animatedMesh(mesh)
{

}

AnimatedMeshNode::~AnimatedMeshNode()
{
	
}

AnimatedMesh* AnimatedMeshNode::getMesh() const
{
	return this->animatedMesh;
}