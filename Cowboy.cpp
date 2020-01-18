#include "Cowboy.h"

#include "AnimatedMesh.h"
#include "AnimatedModelLoader.h"

AnimatedMeshNode* Cowboy::buildCowboy()
{
	AnimatedMesh* animatedMesh = AnimatedModelLoader::loadAnimatedMesh("meshes/model.dae", "");

	// material parameters
	Material material = { glm::vec4(0.5, 0.5, 0.5, 1.0),
						glm::vec4(0.5, 0.5, 0.5, 1.0),
						glm::vec4(0.5, 0.5, 0.5, 1.0),
						3.0f };

	AnimatedMeshNode* animatedModel = new AnimatedMeshNode(animatedMesh, material, vec3(0, 0, 0), vec3(100, 100, 100), vec3(-45, 0, 0));

	return animatedModel;
}