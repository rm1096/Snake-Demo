#ifndef FOOD_H_
#define FOOD_H_
#include "pos.h"
#include <vector>
#include<stdio.h>
#include<stdlib.h>

class Food{
public:
	Position pos;
	void update(std::vector<Position> &body,int hx,int hy); // function to update random food position
};

#endif