#ifndef Forest_H
#define Forest_H
#include <vector>
#include <string>
#include <iostream>
//#include "Tree.h"
#include <Windows.h>
#include <utility>
using std::vector;
using std::pair;
using std::make_pair;

// tree States
static char untouched = '&';
static char burning = 'X';
static char dead = '.';
static char boundry = '#';


// Parameters
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

// forest grid size to simulate
const int sizeX = 19;  
const int sizeY = 19;
class Tree;

class Parameters {

public:

	int mapGenMode;
	int randomGenProbability;
	int weather;
	int windDirection; // 1 = N || 2 = E || 3 = S || 4 = W || 5 = NE || 6 = SE || 7 = SW || 8 = NW
	int windSpeed; // 1 = None || 2 = Low || 3 = High

	vector<pair<int, int>> forestSize = { {sizeX + 2,sizeY + 2} }; // +2 offset is for boundries
	vector<pair<int, int>> fireStartCoordinate = { {0,0} };
};

class Forest
{

	void generateTrees();
public:
	vector<Tree*> *untouchedTreeVector;
	vector<Tree*> *burningTreeVector;
	Parameters params;
	char forestMap[sizeX + 2][sizeY + 2];
	//vector<vector<char>> forestMap;                        // if wanted to specify map size, use this vector
	Forest(Parameters params);
	~Forest();
	void displayForest();

	void updateMap();
	void surroundingTreeFate(Tree tree);


};

class Tree
{

	int lifePoints = 2;   // will only burn 1 iteration   |    0 = empty    1 = burning    2 = untouched 

public:
	char state; // & = Alive |  X = Burning |   = Empty
	int pos_x, pos_y;
	Forest* location;
	int dryness;

	Tree(int x, int y, Forest* forest);
	~Tree();
	void cycleState();
	Tree* clone();
};

#endif // DEBUG
