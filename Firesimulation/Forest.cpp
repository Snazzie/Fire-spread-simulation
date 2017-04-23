#include "Forest.h"

Forest::Forest()
{
	treeVector = new vector<Tree*>(); // initiate vector
	burningTreeVector = new vector<Tree*>();
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
			std::cout << ' ';
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

void Forest::addTree(Tree* tree)
{
	treeVector->push_back(tree);
}


void Forest::updateMap()
{
	//move and delete any non untouched trees from treevector
	for (unsigned int i = 0; i < treeVector->size(); i++)
	{
		if ((*treeVector)[i]->state != untouched)
		{
			
			int X = (*treeVector)[i]->pos_x;
			int Y = (*treeVector)[i]->pos_y;
			
			(*burningTreeVector).push_back((*treeVector)[i]->clone());

			//treeVector->erase(treeVector->begin() + i);
		}
	}

	//delete any dead trees in burning vector  and update map
	for (unsigned int i = 0; i < burningTreeVector->size(); i++)
	{
		

		if ((*burningTreeVector)[i]->state == burning)
		{
			Tree temp = *(*burningTreeVector)[i];
			int X = temp.pos_x;
			int Y = temp.pos_y;
			forestMap[X][Y] = temp.state;
		}
		else if ((*burningTreeVector)[i]->state == dead)
		{
			Tree temp = *(*burningTreeVector)[i];
			int X = temp.pos_x;
			int Y = temp.pos_y;
			forestMap[X][Y] = dead;
			//burningTreeVector->erase(burningTreeVector->begin() + i);
		}
		int in = 0;
	}

}
void Forest:: surroundingTreeFate(Tree tree)
{
	int dir = 0; // Set direction to zero

	//Declare and initialize a Direction Array for the 8 locations around a tree
	int dirAry[8][2] = { { -1,-1 },{ -1,0 },{ -1,-1 },{ 0,-1 },{ 0,1 },{ 1,-1 },{ 1,0 },{ 1,1 } };
	//This while loop scans through the Direction Array to help determine
	// the probability of neighboring trees being on fire
	while (dir < 8)
	{
		int X = tree.pos_x + dirAry[dir][0];
		int Y = tree.pos_y + dirAry[dir][1];
		if (forestMap[X][Y] == untouched) {
			// calculate fate
			if (rand() % 100 < 50)
			{
				// get tree object and set it on fire
				//forest.getTree(X, Y).cycleState(forest);

				for (int i = 0; i < treeVector->size(); i++)
				{


					if ((*treeVector)[i]->pos_x == X && (*treeVector)[i]->pos_y == Y) 
					{
						//cout << forest.treeVector[i].pos_x << forest.treeVector[i].pos_y << "state: " << forest.treeVector[i].state << endl;
						(*treeVector)[i]->cycleState();
						//forest.burningTreeVector.push_back(forest.treeVector[i].clone());
						//forest.forestMap[X][Y] = forest.burningTreeVector[i].state;
					}
				}
			}
			else
			{
				dir++;
			}
		}
		else
		{
			for (int i = 0; i < (*burningTreeVector).size(); i++)
			{

				if ((*burningTreeVector)[i]->pos_x == X && (*burningTreeVector)[i]->pos_y == Y) {
					//cout << forest.treeVector[i].pos_x << forest.treeVector[i].pos_y << "state: " << forest.treeVector[i].state << endl;
					(*burningTreeVector)[i]->cycleState();
					forestMap[X][Y] = (*burningTreeVector)[i]->state;
				}
			}
			dir++;
		}
	}
}

Tree::Tree(int x, int y)
{
	pos_x = x;
	pos_y = y;
	state = untouched;
}



void Tree::cycleState()
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

	//forest.forestMap[pos_x][pos_y] = state;  // update state on map

											 // delete tree object if it is dead
	if (state == dead)
	{
		delete this;
	}
}

Tree* Tree::clone()
{
	Tree* newTree = new Tree(pos_x,pos_y);
	newTree->state = state;
	newTree->lifePoints = lifePoints;
	return newTree ;
}