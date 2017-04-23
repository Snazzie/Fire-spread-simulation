
#include <iostream>
#include <cstdlib>
#include <string>
//#include "Tree.h"
#include "Simulation.h"

using namespace std;


class Simulation;


Forest* forest;
bool redraw = true;

//  generate map
//  for each tree generate a tree object
//  set burn start location
//  calculate catch fire event
//  cycle tree life
//  generate blank map
//  place tree objects to original location
//  calculate catch fire event



int main(void)
{
	


	string input;
	bool restart = true;
	while (restart)
	{
		Simulation sim = Simulation();
		sim.setParams();


		sim.start();
		system("cls");
		cout << "Press Enter for another simulation, or any alphanumeric key to exit>" << endl;
		getline(cin, input);
		//redraw = true;
		if (input != "")
		{
			restart = false;
		}

	}




	return 0;
}









