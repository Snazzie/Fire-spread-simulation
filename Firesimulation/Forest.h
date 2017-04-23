#ifndef Forest_H
#define Forest_H
#include <vector>
#include <string>
#include <iostream>
//#include "Tree.h"
#include <Windows.h>

using std::vector;


static char untouched = '&';
static char burning = 'X';
static char dead = '.';
static char boundry = '#';

// generation modes
const int fullMap = 1;
const int randomMap = 2;

class Tree;

class Params {
public:
	int mapGenMode;
	int randomGenProbability;
};

class Forest
{
public:
	vector<Tree*> *treeVector;
	vector<Tree*> *burningTreeVector;
	char forestMap[21][21];

	Forest(Params params);
	~Forest();
	void displayForest();
	
	
	void updateMap();
	void surroundingTreeFate(Tree tree);

private:
	void generateTrees();
	void addTree(Tree* tree);
};

class Tree 
{
public:
	char state; // & = Alive |  X = Burning |   = Empty
	int pos_x, pos_y;
	int lifePoints = 2;   // will only burn 1 iteration   |    0 = empty    1 = burning    2 = untouched 
	Forest* location;

	
	Tree(int x, int y, Forest* forest);
	~Tree();
	void cycleState();
	Tree* clone();
};

#endif // DEBUG
