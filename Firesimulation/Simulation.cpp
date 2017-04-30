#include "Simulation.h"

Simulation::Simulation()
{
	params = Parameters();
}
Simulation::~Simulation() {}

///<summary>
/// set parameters in object for initiating Forest
///</summary>
void Simulation::setParameters()
{
	// set map generation mode
	while (params.mapGenMode > randomMap || params.mapGenMode < fullMap)
	{
		std::system("cls");
		std::cout << "Please choose a mode" << endl << endl;
		std::cout << "Map Modes: 1 = Full Map | 2 = Random Map" << endl << endl;
		std::cout << "Mode: ";
		if (!(cin >> params.mapGenMode))
		{
			std::cin.clear();
			std::cin.ignore();
			params.mapGenMode = 0;
		}
	}
	// set map gen probability
	if (params.mapGenMode == randomMap)
	{
		while (params.randomGenProbability < 50 || params.randomGenProbability > 100)
		{
			std::system("cls");
			std::cout << "MODE: Random Map Generation" << endl << endl;
			std::cout << "A probability is needed for generating a tree in each cell" << endl << endl;
			std::cout << "Enter a number between 50 and 100: ";
			if (!(std::cin >> params.randomGenProbability))
			{
				std::cin.clear();
				std::cin.ignore();
				params.randomGenProbability = 0;
			}
		}
	}
	// set weather
	while (params.weather > heavyRain || params.weather < drought)
	{
		std::system("cls");
		std::cout << "Please choose a weather" << endl << endl;
		std::cout << "1 = Drought | 2 = Sunny | 3 = Light Rain | 4 = Heavy Rain " << endl << endl;

		std::cout << "Weather: ";
		if (!(std::cin >> params.weather))
		{
			std::cin.clear();
			std::cin.ignore();
			params.weather = 0;
		}
	}

	// set wind speed
	while (params.windSpeed > high || params.windSpeed < none)
	{
		std::system("cls");
		std::cout << "Please choose the wind speed" << endl << endl;
		std::cout << "1 = No wind | 2 = Low | 3 = High" << endl << endl;
		std::cout << "Wind: ";

		if (!(std::cin >> params.windSpeed))
		{
			std::cin.clear();
			std::cin.ignore();
			params.windSpeed = 0;
		}
	}

	// set wind direction
	if (params.windSpeed != none)
	{
		while (params.windDirection > northWest || params.windDirection < north)
		{
			std::system("cls");
			std::cout << "Please choose a wind direction" << endl << endl;
			std::cout << "1 = north  | 2 = East | 3 = South | 4 = West" << endl;
			std::cout << "5 = North East | 6 = South East | 7 = South West | 8 = North West" << endl << endl;
			std::cout << "Wind Direction: ";

			if (!(std::cin >> params.windDirection))
			{
				std::cin.clear();
				std::cin.ignore();
				params.windDirection = 0;
			}
		}
	}
}

///<summary>
/// Simulation initiation, increment and display handling
///</summary>
bool Simulation::start()
{
	bool sameSim = true;

	while (sameSim == true)
	{
		std::system("cls");
		string input;
		int incrementCount = 0;
		int startingTreeCount;
		bool redraw = true;

		// Generate forest
		forest = new Forest(params);

		// get fire start location from user
		while (!(params.fireStartCoordinate[0].first > 0 && params.fireStartCoordinate[0].first < params.forestSize[0].first - 1) &&
			!(params.fireStartCoordinate[0].second > 0 && params.fireStartCoordinate[0].second < params.forestSize[0].second - 1))
		{
			std::system("cls");
			forest->displayForest();

			std::cout << "Where to start the fire?" << endl << endl;
			std::cout << "Format = X,Y || Rule: Must be within border" << endl << endl;
			std::cout << "X: ";
			int x, y;
			if (!(std::cin >> x))
			{
				std::cin.clear();
				std::cin.ignore();
				x = 0;
			}
			std::cout << "Y: ";
			if (!(std::cin >> y))
			{
				std::cin.clear();
				std::cin.ignore();
				y = 0;
			}
			if ((x > 0 && x < params.forestSize[0].first - 1) && (y > 0 && y < params.forestSize[0].second - 1))
			{
				params.fireStartCoordinate[0].first = x;
				params.fireStartCoordinate[0].second = y;
			}
		}
		std::system("cls");

		startingTreeCount = forest->untouchedTreeVector->size();

		// set fire start position
		forest->forestMap[params.fireStartCoordinate[0].first][params.fireStartCoordinate[0].second] = burning;

		// display fire start position before simulation starts
		forest->displayForest();

		std::system("PAUSE");

		// move the tree that is going to be set afire into burning vector to start cycle
		for (int i = 0; i < forest->untouchedTreeVector->size(); i++)
		{
			if ((*forest->untouchedTreeVector)[i]->pos_x == params.fireStartCoordinate[0].first && (*forest->untouchedTreeVector)[i]->pos_y == params.fireStartCoordinate[0].second)
			{
				(*forest->burningTreeVector).push_back((*forest->untouchedTreeVector)[i]->clone());
				(*forest->untouchedTreeVector).erase((*forest->untouchedTreeVector).begin() + i);
				break;
			}
		}
		// increment
		forest->updateMap();

		// Display the forest map
		forest->displayForest();

		// Start simulation
		while (redraw == true)
		{
			std::cout << endl << "Press Enter for time increment, or any alphanumeric key to exit>" << endl;
			std::getline(std::cin, input);

			// end simulation if input is not empty
			if (input != "")
			{
				redraw = false;
				forest->burningTreeVector->clear();
			}
			else
			{
				incrementCount++;

				// save initial vector size due to vector size changing during fire spread proccess
				int size = (*forest->burningTreeVector).size();

				// proccess fire spread on all burning trees
				for (unsigned int i = 0; i < size; i++)
				{
					forest->surroundingTreeFate(*(*forest->burningTreeVector)[i]);
				}

				// increment
				forest->updateMap();
			}

			// show end screen if there are no more burning trees
			if (forest->burningTreeVector->size() == 0)
			{
				redraw = false;

				int input2 = 0;
				while (input2 < 1 || input2 > 2)
				{
					std::system("cls");
					forest->displayForest();

					std::cout << "Trees Started With: " << startingTreeCount << endl;
					std::cout << "Trees Left: " << forest->untouchedTreeVector->size() << endl;
					std::cout << "Trees Died: " << startingTreeCount - forest->untouchedTreeVector->size() - forest->burningTreeVector->size() << endl;
					std::cout << "Simulation Ended After " << incrementCount << " Ticks" << endl << endl;;

					std::cout << "Would you like to do another simulation with the same params?" << endl << endl;

					std::cout << "1 = Yes" << endl;
					std::cout << "2 = Return to menu" << endl;
					std::cout << "3 = Exit Software" << endl << endl;
					std::cout << "Option: ";
					if (!(std::cin >> input2))
					{
						std::cin.clear();
						std::cin.ignore();
						std::system("cls");
						input2 = 0;
					}
					else
					{
						switch (input2)
						{
						case 1: {sameSim = true; break; }
						case 2: {sameSim = false; return true; }
						case 3: {sameSim = false; return false;	 }
						}
					}
				}
				delete forest;
			}
			else // if there are still burning trees
			{
				std::system("cls");
				forest->displayForest();
				std::cout << "Tick: " << incrementCount << endl;

				if (forest->params.windSpeed != 0)
				{
					std::cout << "Wind Direction: ";
					switch (forest->params.windDirection)
					{
					case 1: {std::cout << "North"; break; }
					case 2: {std::cout << "East"; break; }
					case 3: {std::cout << "South"; break; }
					case 4: {std::cout << "West"; break; }
					case 5: {std::cout << "North East"; break; }
					case 6: {std::cout << "South East"; break; }
					case 7: {std::cout << "South West"; break; }
					case 8: {std::cout << "North West"; break; }
					}
					std::cout << endl;
					std::cout << "Wind Speed: ";
					switch (forest->params.windSpeed)
					{
					case 2: {std::cout << "Low"; break; }
					case 3: {std::cout << "High"; break; }
					}
					std::cout << endl;
				}
				else
				{
					std::cout << "Wind: None" << endl;
				}
				std::cout << "Weather: ";
				switch (forest->params.weather)
				{
				case 1: {std::cout << "Drought"; break; }
				case 2: {std::cout << "Sunny"; break; }
				case 3: {std::cout << "Light Rain"; break; }
				case 4: {std::cout << "Heavy Rain"; break; }
				}
				std::cout << endl;

				std::cout << "Untouched Trees: " << forest->untouchedTreeVector->size() << endl;
				std::cout << "Trees On Fire: " << forest->burningTreeVector->size() << endl;
				std::cout << "Trees Died: " << startingTreeCount - forest->untouchedTreeVector->size() - forest->burningTreeVector->size() << endl;
			}
		}
	}
}