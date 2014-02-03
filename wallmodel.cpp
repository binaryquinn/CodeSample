#include "wallmodel.h"
#include "lengthnode.h"
#include <QObject>
#include <string>


WallModel::WallModel()
{	

	shortLength = 3.0f;
	longLength = 4.5f;
	wallWidth = 3.0f;
	wallHeight = 1;
	combinationCount = 0;
}
WallModel::~WallModel()
{
	permutations.clear();
	goodNeighbors.clear();
	lookup.clear();
}

int WallModel::getWallHeight() const
{
	return wallHeight;
}

void WallModel::setWallHeight(int value)
{
	wallHeight = value;
}

float WallModel::getWallWidth() const
{
	return wallWidth;
}

void WallModel::setWallWidth(float value)
{
	wallWidth = value;
}

float WallModel::getLongLength() const
{
	return longLength;
}

float WallModel::getShortLength() const
{
	return shortLength;
}
unsigned long long WallModel::getCombinationCount() const
{
	return combinationCount;
}

int WallModel::getLayerCount() const
{
	return permutations.empty()? 0: permutations.size();
}


void WallModel::build()
{
	permutations.clear();
	goodNeighbors.clear();
	lookup.clear();
	combinationCount = 0;
	rootNode = new LengthNode();
	emit treeState();
	buildTree(rootNode,0.0f);
	extractPermutations(rootNode,vector<float>());
	rootNode->razeTree();
	goodNeighbors.resize(permutations.size());
	emit comparisonState();
	findGoodNeighbors();


	if(wallHeight == 1)
	{
		combinationCount = goodNeighbors.size();
	}
	else
	{
		for(unsigned int layers = 0; layers < goodNeighbors.size();layers++)
		{
			combinationCount+= calculateCombinations(layers, wallHeight);
		}
	}
	emit resultState();

}

void  WallModel::buildTree(LengthNode *parentNode, float currentLength)
{

	if(currentLength < wallWidth)
	{
		float testLength = wallWidth-(currentLength+shortLength);


		if(( testLength > 1.5f) )
		{

			parentNode->shortNode = new LengthNode();
			buildTree(parentNode->shortNode, currentLength+shortLength);
		}
		testLength = wallWidth-(currentLength+longLength);
		if(( testLength > 1.5f) )
		{
			parentNode->longNode = new LengthNode();
			buildTree(parentNode->longNode, currentLength+longLength);
		}
	}
}

void WallModel::extractPermutations(LengthNode *root, vector <float> possibility)
{
	bool reset = false;
	if(root->shortNode)
	{
		if(possibility.empty())
		{
			possibility.push_back(shortLength);
			reset = true;
		}
		possibility.push_back(possibility.back() + shortLength);

		extractPermutations(root->shortNode,vector<float>(possibility));
	}

	if(root->longNode)
	{
		if(reset == true)
		{
			possibility.clear();
			possibility.push_back(longLength);
		}
		else
		{
			possibility.push_back(possibility.back() + longLength);
		}
		extractPermutations(root->longNode,vector<float>(possibility));
	}

	if(!root->shortNode && !root->longNode )
	{

		permutations.push_back(possibility);
	}
}


bool WallModel::containsMatch(vector<float> first, vector<float> second)
{
	vector <float>::iterator firstPos = first.begin(), secondPos = second.begin();
	while((firstPos != first.end() && (secondPos != second.end())))
	{
		if(*firstPos == *secondPos)
			return true;
		else if(*firstPos > *secondPos)
			secondPos++;
		else
			firstPos++;
	}
	return false;
}


void WallModel::findGoodNeighbors()
{
	for(unsigned int current = 0; current < (permutations.size() - 1) ;current++)
	{
		unsigned int comparator =  current + 1;
		for( ; comparator < permutations.size(); comparator++)
		{
			if(!containsMatch(permutations.at(current), permutations.at(comparator)))
			{
				goodNeighbors.at(current).push_back(comparator);
				goodNeighbors.at(comparator).push_back(current);
			}
		}
	}


}

unsigned long long WallModel::calculateCombinations(unsigned int pos, int depth)
{

	if(!lookup.contains(string(pos+","+depth)))
	{
		unsigned long long value = 0;
		if(depth == 0)
			value = goodNeighbors[pos].size();
		else
		{

			for(unsigned int line = 0; line < goodNeighbors[pos].size();line++)
			{
				value+= + calculateCombinations( goodNeighbors[pos][line], (depth-1));
			}

		}

		lookup[string(pos+","+depth)] = value;
		return value;
	}
	else
		return lookup[string(pos+","+depth)];
}


