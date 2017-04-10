// mapview.cpp
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Tree.h"
#include "Forest.h"
using namespace std;


void sim();
void GenerateTree(int coordinate[1][1]);

char untouched = '&';
char burning = 'X';
char dead, boundry = '\n';

//vector<Tree> trees;



void sim()
{
	//vector<Tree> trees;
	int iterationCount = 0;
	Forest forest = Forest();

	// Generate


	// Set the middle cell as a burning tree.
	forest.forestMap[10][10] = 'X';

	string input;
	bool redraw = true;

	// Start the simulation
	while (redraw == true)
	{
		// Display the forest map
		forest.DisplayForest();

		// There are several ways to achieve Enter key recognition; this is one way
		cout << "Press Enter for time increment, or any alphanumeric key to exit>" << endl;
		getline(cin, input);

		if (input != "")
			redraw = false;
		else
		{
			// Lets expand the fire rather arbitrarily - in reality would use rules and occur many times
			/*forestMap[9][9] = 'X';
			forestMap[9][10] = 'X';
			forestMap[9][11] = 'X';
			forestMap[10][9] = 'X';
			forestMap[10][10] = '.';
			forestMap[10][11] = 'X';
			forestMap[11][9] = 'X';
			forestMap[11][10] = 'X';
			forestMap[11][11] = 'X';*/
		}
	}
}

int main(void)
{
	sim();



	return 0;
}



void GenerateTree(int coordinate[1][1])
{
	Tree tree = Tree(coordinate);  // new tree
	//trees.push_back(tree);
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