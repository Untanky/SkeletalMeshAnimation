#pragma once

#include "Texture.h"
#include "AnimatedMesh.h"
#include "JointData.h"
#include "MeshData.h"

class AnimatedModelLoader
{
public:
	static AnimatedMesh* loadAnimatedMesh(const std::string& modelFilepath, const std::string& textureFilepath);

private:
	static Texture* loadTexture(const std::string& textureFilepath);
	
	static VAO* createMesh(const MeshData meshData);

	static Joint* createJoints(JointData* jointData, bool isRoot);
};

