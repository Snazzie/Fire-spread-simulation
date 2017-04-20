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
static char dead, boundry = '\n';

class Tree;

class Forest
{
public:
	vector<Tree> treeVector;
	char forestMap[21][21];

	Forest();
	void displayForest();
	void addTree(Tree &tree);
	Tree getTree(int posX, int posY);
};

class Tree
{
public:
	char state; // & = Alive |  X = Burnt |   = Empty
	int pos_x, pos_y;
	int lifePoints = 2;   // will only burn 1 iteration   |    0 = empty    1 = burning    2 = untouched 

	Tree(int x, int y);
	void cycleState(Forest forest);
};

#endif // DEBUG
