#pragma once

#include "VertexSkinData.h"
#include <string>

using namespace std;

class SkinningData
{
public:
	const vector<string> jointOrder;
	const vector<VertexSkinData> verticesSkinData;

	SkinningData(const vector<string> jointOrder, const vector<VertexSkinData> verticesSkinData)
		: jointOrder(jointOrder), verticesSkinData(verticesSkinData)
	{ }
};