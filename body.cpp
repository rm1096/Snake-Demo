#include "body.h"

void Body::move(int x1,int y1){
	for (int i = count() - 1; i > 0; i --){ //for loop used to iterate through the body
		body_[i].x = body_[i-1].x; //shift the body position in order to make movement
		body_[i].y = body_[i-1].y;}
	body_[0].x = x1;
	body_[0].y = y1;
}
