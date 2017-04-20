#include "Forest.h"

Forest::Forest()
{
	treeVector = vector<Tree>(); // initiate vector

	for (int y = 0; y < 21; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			if (y == 0 || y == 20) 
			{
				forestMap[y][x] = boundry;  // North and south boundary layers
			}
			else if (x == 0 || x == 20) 
			{
				forestMap[y][x] = boundry;  // East and west boundary layers
			}
			else
			{
				forestMap[y][x] = untouched;  // Everything else
			}
		}
	}
}

void Forest::displayForest()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int y = 0; y < 21; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			if (forestMap[y][x] == untouched) {
				SetConsoleTextAttribute(hConsole, 10); // green
			}
			else if (forestMap[y][x] == burning)
			{
				SetConsoleTextAttribute(hConsole, 12); // red
			}
			else if (forestMap[y][x] == boundry)
			{
				SetConsoleTextAttribute(hConsole, 15); // white
			}

			std::cout << forestMap[y][x];
		}
		std::cout << std::endl;
	}
}

void Forest::addTree(Tree &tree)
{
	treeVector.push_back(tree);
}

Tree Forest::getTree(int posX, int posY)
{
	for (unsigned int i = 0; i<treeVector.size(); i++)
	{
		if (treeVector[i].pos_x == posX && treeVector[i].pos_y == posY)
		{
			return treeVector[i];
		}
	}
	// temporary
	Tree null = Tree(0,0);
	return null;
}


Tree::Tree(int x, int y)
{
	pos_x = x;
	pos_y = y;
	state = untouched;
}



void Tree::cycleState(Forest forest)
{

	if (lifePoints < 0)
	{
		lifePoints--;
	}

	if (lifePoints == 1)
	{
		state = burning;

	}
	if (lifePoints == 0)
	{
		state = dead;
	}

	forest.forestMap[pos_x][pos_y] = state;  // update state on map

											 // delete tree object if it is dead
	if (state == dead)
	{
		delete this;
	}
}
