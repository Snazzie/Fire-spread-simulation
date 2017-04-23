#include "Simulation.h"


Simulation::Simulation()
{
	
	params = Params();

}
Simulation::~Simulation() {}

void Simulation::setParams()
{
	params.mapGenMode = 0;
	
	while (params.mapGenMode > 2 || params.mapGenMode < 1)
	{
		system("cls");
		cout << "Please choose a mode" << endl;
		cout << "Map Modes: 1 = Full Map  | 2 = Random Map" << endl;
		cout << "Mode: ";
		cin >> params.mapGenMode;
	}
	if (params.mapGenMode == randomMap)
	{

		while (params.randomGenProbability < 50)
		{
			std::system("cls");
			std::cout << "MODE: Random Map Generation" << std::endl << std::endl;
			std::cout << "A probability is needed for generating a tree in each cell." << std::endl << std::endl;

			std::cout << "Enter a number between 50 and 100: ";
			std::cin >> params.randomGenProbability;
		}

	}
}

void Simulation::start()
{
	bool sameSim = true;
	while (sameSim)
	{

		system("cls");

		int incrementCount = 0;
		int startingTreeCount;
		bool redraw = true;
		// Generate

		forest = new Forest(params);

		startingTreeCount = forest->treeVector->size();


		for (int i = 0; i < forest->treeVector->size(); i++)
		{


			if ((*forest->treeVector)[i]->pos_x == 10 && (*forest->treeVector)[i]->pos_y == 10)
			{
				//(*forest.treeVector)[i]->cycleState();  // set fire

				(*forest->burningTreeVector).push_back((*forest->treeVector)[i]->clone());
				(*forest->treeVector).erase((*forest->treeVector).begin() + i);
				break;
			}
		}
		forest->updateMap();

		string input;


		// Display the forest map
		forest->displayForest();

		// Start the simulation

		while (redraw == true || forest->burningTreeVector->size() < 0)
		{
			incrementCount++;
			// There are several ways to achieve Enter key recognition; this is one way

			cout << "Press Enter for time increment, or any alphanumeric key to exit>" << endl;
			getline(cin, input);
			//input = "";
			if (input != "")
			{
				redraw = false;
			}
			else
			{


				vector<Tree*> temp = (*forest->burningTreeVector);
				for (int i = 0; i < temp.size(); i++)   // go through all burning trees
				{

					forest->surroundingTreeFate(*(*forest->burningTreeVector)[i]);


				}
				forest->updateMap();
				system("cls");
				forest->displayForest();



				cout << endl;
				if (forest->burningTreeVector->size() == 0)
				{
					redraw = false;


					cout << "Trees Started With: " << startingTreeCount << endl;
					cout << "Trees Left: " << forest->treeVector->size() << endl;
					cout << "Simulation Ended after " << incrementCount << " Ticks" << endl;
					delete forest;
				}
				else
				{
					cout << "Tick: " << incrementCount << endl;
					cout << "Untouched Trees: " << forest->treeVector->size() << endl;
					cout << "Trees On Fire: " << forest->burningTreeVector->size() << endl;
					Sleep(50);
				}


			}

		}
		system("PAUSE");
		system("cls");
		cout << "Press Enter to start another simulation with same parameters, or any alphanumeric key to exit>" << endl;
		getline(cin, input);
		//input = "";
		if (input != "")
		{
			sameSim = false;
		}

	}
	
}


