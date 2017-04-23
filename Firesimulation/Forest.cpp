#include "Forest.h"

Forest::Forest(Params params )
{
	std::system("cls");
	
	
	

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
			else if (x == 10 && y == 10)  // always have a tree in center
			{
				forestMap[y][x] = untouched;
			}
			else
			{
				if (params.mapGenMode == fullMap)
				{
					forestMap[y][x] = untouched;
				}
				else 
				{
					if (rand() % 100 < params.randomGenProbability) // make map unique 
					{
						forestMap[y][x] = untouched;  // Everything else
					}
				}
				
			}

		}
	}
	generateTrees();

}
Forest::~Forest() {}
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
			else if (forestMap[y][x] == dead)
			{
				SetConsoleTextAttribute(hConsole, 14); // white
			}

			std::cout << forestMap[y][x];
		}
		std::cout << std::endl;
	}

}

void Forest::addTree(Tree* tree)
{
	//tree->location = this;
	treeVector->push_back(tree);
}
void Forest::generateTrees()
{

	for (int y = 0; y < 21; y++)
	{
		for (int x = 0; x < 21; x++)
		{
			if (forestMap[x][y] == untouched)
			{
				Tree* tree = new Tree(x, y,this);  // new tree

				addTree(tree);  // add tree to list
			}
		}
	}



}

void Forest::updateMap()
{
	////move and delete any non untouched trees from treevector
	//for (unsigned int i = 0; i < treeVector->size(); i++)
	//{
	//	if ((*treeVector)[i]->state != untouched)
	//	{

	//		int X = (*treeVector)[i]->pos_x;
	//		int Y = (*treeVector)[i]->pos_y;

	//		(*burningTreeVector).push_back((*treeVector)[i]->clone());

	//		treeVector->erase(treeVector->begin() + i);
	//	}
	//}

	//delete any dead trees in burning vector  and update map

	for (unsigned int i = 0; i < burningTreeVector->size(); i++)
	{
		(*burningTreeVector)[i]->cycleState();

		Tree* temp = (*burningTreeVector)[i];
		int X = temp->pos_x;
		int Y = temp->pos_y;


		if (temp->state == burning)
		{

			temp->location->forestMap[X][Y] = temp->state;  // update state on map

		}
		else if (temp->state == dead)
		{
			temp->location->forestMap[X][Y] = temp->state;  // update state on map
			burningTreeVector->erase(burningTreeVector->begin() + i);

			i--; // -1 to i to 
			// delete object
		}

		//(*treeVector)[i]->cycleState(); // cycle for next interval    tree should be dead now
	}

}
void Forest::surroundingTreeFate(Tree tree)
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
		if (forestMap[X][Y] == untouched)
		{
			// calculate fate
			if (rand() % 100 < 50)
			{
				// get tree object and set afire

				for (int i = 0; i < treeVector->size(); i++)
				{


					if ((*treeVector)[i]->pos_x == X && (*treeVector)[i]->pos_y == Y)
					{
						//forestMap[X][Y] = burning;
						//system("PAUSE");
						(*burningTreeVector).push_back((*treeVector)[i]->clone());
						(*treeVector).erase((*treeVector).begin() + i);
						//(*treeVector)[i]->cycleState(); // set fire

					}
				}
			}

		}
		dir++;

	}
}

Tree::Tree(int x, int y, Forest* forest)
{
	location = forest;
	pos_x = x;
	pos_y = y;
	state = untouched;
}

Tree::~Tree()
{
	//Location->forestMap[pos_x][pos_y] = state;
}


void Tree::cycleState()
{

	if (lifePoints > 0)
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




}

Tree* Tree::clone()
{
	Tree* newTree = new Tree(pos_x, pos_y, location);
	newTree->state = state;
	newTree->lifePoints = lifePoints;

	return newTree;
}