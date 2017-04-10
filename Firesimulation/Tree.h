#ifndef Tree_H
#define Tree_H
#include <iostream>
#include <cstdlib>
#include <conio.h>
using namespace std;

char untouched = '&';
char burning = 'X';
char dead, boundry = '\n';

class Tree
{
public:
	char state; // & = Alive |  X = Burnt |   = Empty
	int gridCoordinate[1][1];
	int lifePoints = 2;   // will only burn 1 iteration   |    0 = empty    1 = burning    2 = untouched 
	Tree* next;

	Tree(int coord[1][1]);
	void CycleState();
	void setNext(Tree *nextTree);
	Tree *getNext();
	void treeFate();
};

class TreeList
{
	Tree *start, *end;

public:
	TreeList();
	void addTree(Tree tree);

};

#endif // 
