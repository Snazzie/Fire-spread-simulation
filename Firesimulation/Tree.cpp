#include "Tree.h"



Tree::Tree(int coord[1][1])
{
	gridCoordinate[1][1] = coord[1][1];
	state = untouched;
}



void Tree::CycleState()
{

	if (lifePoints < 0)
	{
		lifePoints--;
	}

	if (lifePoints == 1)
	{
		state = burning;
	}
	if (lifePoints == 0)
	{
		state = dead;
	}

}
void Tree::setNext(Tree *nextTree)
{
	next = nextTree;
}

Tree* Tree::getNext()
{
	return next;
}

TreeList::TreeList() 
{
	start = NULL;   // both set to NULL
	end = NULL;
}

void TreeList::addTree(Tree tree)
{
	cout << "Adding tree:" << tree.gridCoordinate << " to List" << endl << endl;

	Tree* current;

	if (end == NULL)
	{// if list is empty

		current = new Tree(tree.gridCoordinate);  // allocate memory
		start = current;               // change start 
		end = current;				  // and end
	}
	else
	{
		current = new Tree(tree.gridCoordinate);   // allocate memory
		end->setNext(current);          // change end's next
		end = current;                  // change end
	}
}
