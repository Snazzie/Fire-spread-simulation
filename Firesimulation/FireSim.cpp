#include "Simulation.h"
#include <ctime>

int main(void)
{
	srand(time(0)); // makes sure generate seed is different every run

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