#pragma once
#ifndef Simulation_H
#define Simulation_H
#include <vector>
#include <string>
#include <iostream>
#include "forest.h"
#include <Windows.h>

using namespace std;


class  Simulation
{
public:
	Forest* forest;
	Params params;

	Simulation();
	~Simulation();
	void setParams();
	bool start();


};

#endif // DEBUG