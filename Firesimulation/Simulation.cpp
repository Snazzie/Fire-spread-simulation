#include "Simulation.h"


Simulation::Simulation()
{
	
	params = Params();

}
Simulation::~Simulation() {}

void Simulation::setParams()
{
	// Map Generation mode
	while (params.mapGenMode > randomMap || params.mapGenMode < fullMap)
	{
		system("cls");
		cout << "Please choose a mode" << endl;
		cout << "Map Modes: 1 = Full Map | 2 = Random Map" << endl;
		cout << "Mode: ";
		if (!(cin >> params.mapGenMode))
		{
			cin.clear();
			cin.ignore();
			params.mapGenMode = 0;
		}

	}
	
	if (params.mapGenMode == randomMap)
	{

		while (params.randomGenProbability < 50 || params.randomGenProbability > 100)
		{
			system("cls");
			cout << "MODE: Random Map Generation" << endl << endl;
			cout << "A probability is needed for generating a tree in each cell." << endl << endl;

			cout << "Enter a number between 50 and 100: ";
			if (!(cin >> params.randomGenProbability))
			{
				cin.clear();
				cin.ignore();
				params.randomGenProbability = 0;
			}


		}

	}

	// Weather 
	while (params.weather > heavyRain || params.weather < drought)
	{
		system("cls");
		cout << "Please choose a weather" << endl;
		cout << "1 = Drought | 2 = Sunny | 3 = Light Rain | 4 = Heavy Rain " << endl;
		cout << "Weather: ";
		if (!(cin >> params.weather))
		{
			cin.clear();
			cin.ignore();
			params.weather = 0;
		}
	}
	// Wind Speed
	while (params.windSpeed > high || params.windSpeed < none)
	{
		system("cls");
		cout << "Wind Speed" << endl;
		cout << "1 = No wind | 2 = Low | 3 = High" << endl;
		cout << "Wind: ";

		if (!(cin >> params.windSpeed))
		{
			cin.clear();
			cin.ignore();
			params.windSpeed = 0;
		}
	}
	// Wind Direction
	if (params.windSpeed != none)
	{
		while (params.windDir > northWest || params.windDir < north)
		{
			system("cls");
			cout << "Wind Direction" << endl;
			cout << "1 = north  | 2 = East | 3 = South | 4 = West" << endl;
			cout << "5 = North East | 6 = South East | 7 = South West | 8 = North West" << endl;
			cout << "Wind Direction: ";

			if (!(cin >> params.windDir))
			{
				cin.clear();
				cin.ignore();
				params.windDir = 0;
			}
		}
	}

}

void Simulation::start()
{
	bool sameSim = true;
	while (sameSim == true)
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

		while (redraw == true)
		{
			
			// There are several ways to achieve Enter key recognition; this is one way
	      
			cout << endl << "Press Enter for time increment, or any alphanumeric key to exit>" << endl;
			getline(cin, input);
			//input = "";
			if (input != "")
			{
				redraw = false;
			}
			else
			{

				incrementCount++;
				vector<Tree*> temp = (*forest->burningTreeVector);
				for (unsigned int i = 0; i < temp.size(); i++)   // go through all burning trees
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
					
					if (forest->params.windSpeed != 0)
					{
						cout << "Wind Direction: ";
						switch (forest->params.windDir)
						{
						case 1:{cout << "North"; break; }
						case 2:{cout << "East"; break; }
						case 3:{cout << "South"; break; }
						case 4:{cout << "West"; break; }
						case 5:{cout << "North East"; break; }
						case 6:{cout << "South East"; break; }
						case 7:{cout << "South West"; break; }
						case 8:{cout << "North West"; break; }
						}
						cout << endl;
						cout << "Wind Speed: ";
						switch (forest->params.windSpeed)
						{
						case 2:{cout << "Low"; break; }
						case 3:{cout << "High"; break; }
						}
						cout << endl;
					}
					else 
					{
						cout << "Wind: None" << endl;
					}
					cout << "Weather: ";
					switch (forest->params.weather)
					{
					case 1: {cout << "Drought"; break; }
					case 2: {cout << "Sunny"; break; }
					case 3: {cout << "Light Rain"; break; }
					case 4: {cout << "Heavy Rain"; break; }
					}
					cout << endl;

					cout << "Untouched Trees: " << forest->treeVector->size() << endl;
					cout << "Trees On Fire: " << forest->burningTreeVector->size() << endl;
					
				}


			}

		}
		int input2 = 0 ;
		while (input2 < 1 || input2 > 2) 
		{
			system("cls");
			cout << "Would you like to do another simulation with the same parameters?" << endl <<endl;
			cout << "1 = Yes" << endl;

			cout << "2 = Return to menu" << endl;
			cout << "Option: ";
			if (!(cin >> input2))
			{
				cin.clear();
				cin.ignore();
				input2 = 0;
			}
			switch (input2)
			{
			case 1: {sameSim = true; break; }
			case 2: {sameSim = false; break; }
			}

			cout << endl;
		}
		

	}
	
}


