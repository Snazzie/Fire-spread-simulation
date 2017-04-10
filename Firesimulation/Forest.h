#ifndef Forest_H
#define Forest_H

#include <string>
#include <iostream>
#include "Tree.h"


using namespace std;

char untouched = '&';
char burning = 'X';
char dead, boundry = '\n';

class Forest
{
public:
	char forestMap[21][21];

	Forest();
	void DisplayForest();

};



#endif // DEBUG
