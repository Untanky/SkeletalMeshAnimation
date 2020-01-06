#include "ColladaLoader.h"

#include "rapidxml-1.13/rapidxml.hpp"

#include "SkinLoader.h";
#include "SkeletonLoader.h"
#include "GeometryLoader.h"

using namespace std;
using namespace rapidxml;

AnimatedModelData ColladaLoader::loadColladaModel(const string& colladaFilepath, unsigned int maxWeights)
{
	string xmlData;

	xml_document<> doc;
	doc.parse<0>(xmlData.c_str);

	SkinLoader* skinLoader = new SkinLoader(doc.first_node("library_controllers\0"), maxWeights);
	SkinningData skinningData = skinLoader->extractSkinningData();

	SkeletonLoader* jointsLoader = new SkeletonLoader(doc.first_node("library_visual_scenes\0"), skinningData.jointOrder);
	SkeletonData jointsData = jointsLoader->extractSkeletonData();

	GeometryLoader* modelLoader = new GeometryLoader(doc.first_node("library_geometries\0"), skinningData.verticesSkinData);
	MeshData meshData = modelLoader->extractModelData();

	return AnimatedModelData(meshData, jointsData);
}