#include "AnimatedModelLoader.h"

#include "ColladaLoader.h"
#include "AnimatedModelData.h"

AnimatedMesh AnimatedModelLoader::loadAnimatedMesh(const std::string& meshFilepath, const std::string& textureFilepath)
{
	AnimatedModelData entityData = ColladaLoader::loadColladaModel(meshFilepath, 50);
	VAO* model = createMesh(entityData.getMeshData());
	SkeletonData skeletonData = entityData.getJointData();
	Joint* headJoint = createJoints(skeletonData.headJoint);
	Texture* texture = loadTexture(textureFilepath);
	return AnimatedMesh(model, texture, headJoint, skeletonData.jointCount);
}

VAO* AnimatedModelLoader::createMesh(MeshData meshData)
{
	VAO* vao = VAO::create();
	vao->bind(std::vector<unsigned int>());
	vao->createIndexBuffer(meshData.getIndices());
	vao->createAttribute(0, meshData.getVertices(), 3);
	vao->createAttribute(1, meshData.getTexCoords(), 2);
	vao->createAttribute(2, meshData.getNormals(), 3);
	vao->createUIntAttribute(3, meshData.getJointIds(), 3);
	vao->createAttribute(4, meshData.getWeights(), 3);
	vao->unbind(std::vector<unsigned int>());
	return vao;
}

Joint* AnimatedModelLoader::createJoints(JointData jointData)
{
	Joint* joint = new Joint(jointData.index, jointData.name, jointData.bindTransform);
	joint->setParent(jointData.parent);

	for each (JointData jd in jointData.children)
	{
		jd.parent = joint;
		createJoints(jd);
	}
	return joint;
}

Texture* AnimatedModelLoader::loadTexture(const std::string& textureFilepath)
{
	return nullptr;
}