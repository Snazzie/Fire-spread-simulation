#ifndef Forest_H
#define Forest_H
#include <vector>
#include <string>
#include <iostream>
//#include "Tree.h"
#include <Windows.h>
#include <utility>
using std::vector;

// tree States
static char untouched = '&';
static char burning = 'X';
static char dead = '.';
static char boundry = '#';

// generation modes
const int fullMap = 1;
const int randomMap = 2;

// weather
const int drought = 1;
const int sunny = 2;
const int lightRain = 3;
const int heavyRain = 4;

// wind Direction
const int north = 1;
const int east = 2;
const int south = 3;
const int west = 4;
const int northEast = 5;
const int southEast = 6;
const int southWest = 7;
const int northWest = 8;

// wind speed
const int none = 1;
const int low = 2;
const int high = 3;

class Tree;

class Params {

public:
	
	int mapGenMode;
	int randomGenProbability;
	int weather;
	int windDir; // 1 = N || 2 = E || 3 = S || 4 = W || 5 = NE || 6 = SE || 7 = SW || 8 = NW
	int windSpeed; // 1 = None || 2 = Low || 3 = High
};

class Forest 
{
public:
	vector<Tree*> *treeVector;
	vector<Tree*> *burningTreeVector;
	char forestMap[21][21];
	Params params;

	Forest(Params parameters);
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
	int dryness;
	int lifePoints = 2;   // will only burn 1 iteration   |    0 = empty    1 = burning    2 = untouched 
	Forest* location;

	
	Tree(int x, int y, Forest* forest);
	~Tree();
	void cycleState();
	Tree* clone();
};

#endif // DEBUG
