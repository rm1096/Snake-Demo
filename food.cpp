#include "food.h"

void Food::update(std::vector<Position> &body,int hx,int hy){ //function to update random food position
    int i;
    int flag = 0; //mark to see if position is valid
    while(1)
	{
        pos.x = (rand() % (ROW - 2)) + 2;
        pos.y = (rand() % (COL - 2)) + 2;
 
     if (pos.x != hx && pos.y != hy) //makes sure position is not same with head
     for(i=0;i<body.size();i++){ //makes sure the position is not same with body
         if (pos.x!=body[i].x && pos.y!=body[i].y){
       	 	flag = 1;}
            }
        if(flag){
		break;}
        continue;
    }
}
