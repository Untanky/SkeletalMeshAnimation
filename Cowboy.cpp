#include "Cowboy.h"

#include "AnimatedMesh.h"
#include "AnimatedModelLoader.h"

AnimatedMesh* Cowboy::buildCowboy()
{
	AnimatedMesh* animatedMesh = AnimatedModelLoader::loadAnimatedMesh("meshes/model.dae", "meshes/diffuse.png");

	return animatedMesh;
}