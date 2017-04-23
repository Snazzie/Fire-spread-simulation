
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
//#include "Tree.h"
#include "Forest.h"

using namespace std;


void sim();
void generateTrees();

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
	
	
	/*for (int i = 0; i < forest.treeVector.size(); i++)
	{
		cout << forest.treeVector[i].pos_x << forest.treeVector[i].pos_y << "state: " << forest.treeVector[i].state  << endl;
	}
	system("PAUSE");*/

	// Set the middle cell as a burning tree.

	//forest.getTree(10,10).cycleState(forest);

	for (int i = 0; i < forest.treeVector->size(); i++)
	{
		

		if ((*forest.treeVector)[i]->pos_x == 10 && (*forest.treeVector)[i]->pos_y == 10) {

			//forest.treeVector[i]->cycleState();
			(*forest.treeVector)[i]->state = burning;
			//forest.treeVector[i]->state = burning;
			//forest.burningTreeVector.push_back(forest.treeVector[i]);
			
			//forest.forestMap[10][10] = forest.burningTreeVector[0]->state;

		}
	}
	forest.updateMap();

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
			

			for (int i = 0; i < forest.burningTreeVector->size(); i++)   // go through all burning trees
			{
				Tree* temp = (*forest.burningTreeVector)[i];
				forest.surroundingTreeFate(*temp);

				// calculate catch fire
			}
			system("cls");
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
				Tree* tree = new Tree(x, y);  // new tree
				
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