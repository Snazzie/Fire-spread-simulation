#pragma once
#ifndef Simulation_H
#define Simulation_H
#include "forest.h"

using namespace std;

class  Simulation
{
public:
	Forest* forest;
	Parameters params;

	Simulation();
	~Simulation();
	void setParameters();
	bool start();
};

#endif // DEBUG