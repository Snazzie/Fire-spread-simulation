#include "Simulation.h"
#include <ctime>

//  generate map
//  for each tree generate a tree object
//  set burn start location
//  calculate catch fire event
//  cycle tree life
//  generate blank map
//  place tree objects to original location
//  calculate catch fire event+



int main(void)
{
	
	srand(time(0)); // makes sure generate seed is different every run

	string input;
	bool restart = true;
	while (restart)
	{
		Simulation* sim = new Simulation();
		sim->setParameters();


		restart = sim->start();  // determine to exit or restart sim
		
		delete sim;


	}




	return 0;
}









