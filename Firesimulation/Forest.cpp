#include "Forest.h"
#include <Windows.h>
Forest::Forest()
{
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
			else
			{
				forestMap[y][x] = untouched;  // Everything else
			}
		}
	}
}

void Forest::DisplayForest()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int y = 0; y < 21; y++)
	{
		for (int x = 0; x < 21; x++)
		{
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

			cout << forestMap[y][x];
		}
		cout << endl;
	}
}
