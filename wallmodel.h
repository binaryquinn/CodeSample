#ifndef WALLMODEL_H
#define WALLMODEL_H
#include "lengthnode.h"
#include <string>
#include <vector>
#include <QMap>
#include <QObject>

using namespace std;

class WallModel: public QObject
{
	 Q_OBJECT

public:
	WallModel();
	~WallModel();
	float getShortLength() const;
	float getLongLength() const;

	float getWallWidth() const;
	void setWallWidth(float value);

	int getWallHeight() const;
	void setWallHeight(int value);

	unsigned long long getCombinationCount() const;

	int getLayerCount() const;

	void build();



signals:
	void treeState();
	void comparisonState();
	void resultState();

private:
	float shortLength;
	float longLength;
	float wallWidth;
	int wallHeight;
	LengthNode *rootNode;
	unsigned long long combinationCount;
	vector< vector<float> > permutations;
	vector< vector<int> > goodNeighbors;
	QMap< string,unsigned long  int> lookup;

	void buildTree(LengthNode *parentNode, float currentLength);
	void extractPermutations(LengthNode *root, vector<float> possibility);
	void findGoodNeighbors();
	bool containsMatch(vector<float> first, vector<float> second);
	unsigned long long calculateCombinations(unsigned int pos, int depth);

};

#endif // WALLMODEL_H
