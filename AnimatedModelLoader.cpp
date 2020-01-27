#include "AnimatedModelLoader.h"

#include "ColladaLoader.h"
#include "AnimatedModelData.h"

AnimatedMesh* AnimatedModelLoader::loadAnimatedMesh(const std::string& meshFilepath, const std::string& textureFilepath)
{
	AnimatedModelData* entityData = ColladaLoader::loadColladaModel(meshFilepath, 50);
	VAO* model = createMesh(entityData->getMeshData());
	SkeletonData skeletonData = entityData->getJointData();
	Joint* headJoint = createJoints(skeletonData.headJoint, true);
	Texture* texture = loadTexture(textureFilepath);
	return new AnimatedMesh(model, texture, headJoint, skeletonData.jointCount);
}

VAO* AnimatedModelLoader::createMesh(MeshData meshData)
{
	VAO* vao = VAO::create();
	vao->bind(std::vector<unsigned int>());
	vao->createIndexBuffer(meshData.getIndices());
	vao->createAttribute(Mesh::attribVertex, meshData.getVertices(), 3);
	vao->createAttribute(Mesh::attribTexCoord, meshData.getTexCoords(), 2);
	vao->createAttribute(Mesh::attribNormal, meshData.getNormals(), 3);
	vao->createUIntAttribute(Mesh::attribJointIndices, meshData.getJointIds(), 3);
	vao->createAttribute(Mesh::attribWeights, meshData.getWeights(), 3);
	vao->unbind(std::vector<unsigned int>());
	return vao;
}

Joint* AnimatedModelLoader::createJoints(JointData* jointData, bool isRoot)
{
	Joint* joint = new Joint(jointData->index, jointData->name, jointData->bindTransform);
	if(!isRoot)
		joint->setParent(jointData->parent);

	for each (JointData* jd in jointData->children)
	{
		jd->parent = joint;
		createJoints(jd, false);
	}
	return joint;
}

Texture* AnimatedModelLoader::loadTexture(const std::string& textureFilepath)
{
	return Texture::newTexture(textureFilepath)->anisotropic()->create();
}