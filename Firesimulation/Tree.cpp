//#include "Forest.h"
//
//
//
//Tree::Tree(int x,int y)
//{
//	pos_x = x;
//	pos_y = y;
//	state = untouched;
//}
//
//
//
//void Tree::cycleState(Forest forest)
//{
//
//	if (lifePoints < 0)
//	{
//		lifePoints--;
//	}
//
//	if (lifePoints == 1)
//	{
//		state = burning;
//		
//	}
//	if (lifePoints == 0)
//	{
//		state = dead;
//	}
//
//	forest.forestMap[pos_x][pos_y] = state;  // update state on map
//
//	// delete tree object if it is dead
//	if (state == dead) 
//	{
//		delete this;
//	}
//}
