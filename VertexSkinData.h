#pragma once

#include <algorithm>

using namespace std;

class VertexSkinData
{
public:
	vector<int> jointIds;
	vector<float> weights;

	void addJointEffect(int jointId, float weight)
	{
		for (int i = 0; i < weights.size(); i++)
		{
			if (weight > weights[i])
			{
				jointIds.insert(jointIds.begin() + i, jointId);
				weights.insert(weights.begin() + i, weight);
				return;
			}
		}

		jointIds.push_back(jointId);
		weights.push_back(weight);
	}

	void limitJointNumber(int max)
	{
		if (jointIds.size() > max)
		{
			vector<float> topWeights;
			float total = saveTopWeights(topWeights);
			refillWeightList(topWeights, total);
			removeExcessJointIds(max);
		}
		else if (jointIds.size() < max)
		{
			fillEmptyWeights(max);
		}
	}

private:
	void fillEmptyWeights(int max)
	{
		while (jointIds.size() < max)
		{
			jointIds.push_back(0);
			weights.push_back(0.f);
		}
	}

	float saveTopWeights(vector<float>& topWeightsList)
	{
		float total = 0;
		for (int i = 0; i < topWeightsList.size(); i++)
		{
			topWeightsList.push_back(weights[i]);
			total += topWeightsList[i];
		}
		return total;
	}

	void refillWeightList(vector<float> topWeights, float total)
	{
		weights.clear();
		for each (float f in topWeights)
		{
			weights.push_back(min(f / total, 1.f));
		}
	}

	void removeExcessJointIds(int max)
	{
		while (jointIds.size() > max)
			jointIds.pop_back();
	}
};