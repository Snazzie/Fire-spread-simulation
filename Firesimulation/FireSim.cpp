
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
//#include "Tree.h"
#include "Forest.h"

using namespace std;


void sim();
void generateTrees();
void surroundingTreeFate(Tree tree);


Forest forest;
bool redraw = true;

//  generate map
//  for each tree generate a tree object
//  set burn start location
//  calculate catch fire event
//  cycle tree life
//  generate blank map
//  place tree objects to original location
//  calculate catch fire event

void sim()
{
	
	int iterationCount = 0;
	
	// Generate
	forest = Forest();
	generateTrees();
	
	

	// Set the middle cell as a burning tree.
	forest.getTree(10,10).cycleState(forest);

	string input;
	

	// Display the forest map
	forest.displayForest();

	// Start the simulation
	while (redraw == true)
	{

		// There are several ways to achieve Enter key recognition; this is one way
		cout << "Press Enter for time increment, or any alphanumeric key to exit>" << endl;
		getline(cin, input);

		if (input != "") 
		{
			redraw = false;
		}
		else
		{
			for (int i = 0; i < forest.treeVector.size(); i++)   // go through all burning trees
			{
				surroundingTreeFate(forest.treeVector[i]);

				// calculate catch fire
			}
			forest.displayForest();
		}
	}
}

int main(void)
{
	while (redraw == true) 
	{
		sim();
	}
		



	return 0;
}



void generateTrees()
{
	for (int y = 0; y < 21; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			if (forest.forestMap[x][y] == untouched)
			{
				Tree tree = Tree(x, y);  // new tree
				
				forest.addTree(tree);  // add tree to list
			}
		}
	}
	
	
}

//char TreeStatus(int coordinate[1][1])
//{
//	for each (Tree tree in trees)
//	{
//		if (tree.gridCoordinate == coordinate)
//		{
//			return tree.state;
//		}
//	}
//}
//

void surroundingTreeFate(Tree tree)
{
	int dir = 0; // Set direction to zero
	bool onFire = false;
	
	//Declare and initialize a Direction Array for the 8 locations around a tree
	int dirAry[8][2] = { {-1,-1},{-1,0},{-1,-1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
	 //This while loop scans through the Direction Array to help determine
		// the probability of neighboring trees being on fire
		while (dir < 8 && !onFire)
		{
			int X = tree.pos_x + dirAry[dir][0];
			int Y = tree.pos_y + dirAry[dir][1];
			if (forest.forestMap[X][Y] == untouched) {
				// calculate fate
				if (rand() % 100 < 50)
				{
					// get tree object and set it on fire
					forest.getTree(X, Y).cycleState(forest);
				}
				else
				{
					dir++;
				}
			}
			else
			{
				dir++;
			}
		}
}
//bool isNeighbourOnFire(char forestMap[21][21], int row, int column)
//{
//	int dir = 0; // Set direction to zero
//	bool onFire = false;
//
//	// Declare and initialize a Direction Array for the 8 locations around a tree
//	int dirAry[8][2] = { {-1,-1},{-1,0},{-1,-1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
//
//	// This while loop scans through the Direction Array to help determine
//	// the probability of neighboring trees being on fire
//	while (dir < 8 && !onFire)
//	{
//		int r = row + dirAry[dir][0];
//		int c = column + dirAry[dir][1];
//
//		if (forestMap[r][c] == burning)
//		{
//			onFire = true;
//		}
//		else
//		{
//			dir++;
//		}
//	}
//	return onFire;
//}