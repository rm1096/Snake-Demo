#include "game.h"

//EXTRA FEATURES: QUIT, SCORE, SPEED, LEVEL UP, INSTRUCTIONS
 
//get_key will return the key user typed
char Game::get_key() 
{
    int n;
    char buf[3];
    n = read(0,buf,sizeof(buf));
    if(3 == n && buf[0] == 27 && buf[1] == 91)
    {
        return buf[2];
    }
    else if(1 == n)
    {
        return buf[0];
    }
    return 0;
}


//need to implement end funtion()
int Game::end()                  //exit game function
{
    pen.goto_xy(ROW + 3,1);  
    system("stty echo icanon");     //restart cache
    pen.show_cur(); //show cursor
    pen.goto_xy(7,35);
    pen.putstr(37, 1, "GAME OVER");
    pen.goto_xy(8,33);
    std::cout<<"FINAL SCORE: "<<score<<std::endl;
    exit(0);                        //exit
}

int Game::getKey()                  //key control function
{
     int quit = 0;
     int flag = 1;
     while(! quit){ //start of infinite loop
     	 char key;
         key = get_key();
         switch(key){
             case UP:
                 snake.head.direction = UP; //set direction of snake head
                 break;
             case DOWN:
                snake.head.direction = DOWN;
                 break;
             case RIGHT:
                 snake.head.direction = RIGHT;
                 break;
             case LEFT:
                 snake.head.direction = LEFT;
                 break;
             case 49: // if the user presses 1, end the game
                 end();
                 break;
             default:
                 break;
         }
         
        
     }
  
}


//function use to draw a box
void Game::drawBox() //draw the outer range
{
    pen.clr_scrn();
    pen.draw_box(1,20,ROW,COL,42,32,'#');
}
 
void Game::drawSnake(void) // draw snake
{
    //TODO
	//need to draw the snake out
	//draw head
	//use loop to draw body
    int i;
    pen.goto_xy(2,6);
    std::cout<<"SCORE: "<<score<<std::endl;
    pen.goto_xy(4,2);
    pen.putstr(25,1,"PRESS '1' TO QUIT");
    if(score == nextLevel){ //implements the Level Up
        nextLevel+=3;
        pen.goto_xy(1,1);
        pen.putstr(35,1, "LEVEL UP!");
        speed -= 60000;
    }
    pen.draw_rect(snake.head.pos.x,snake.head.pos.y + 20, 1, 1, 43, 3, 'x'); //this draws the snake head
    
     for (i=0; i <= snake.body.count()-1;i++){
         pen.draw_rect(snake.body.body_[i].x,snake.body.body_[i].y + 20, 1, 1, 3, 32, '='); //this draws the snake body
     }
}

void Game::snakeMove(void){//move snake
    
	//TODO
	//need to check if the head space is valid 
	//if it is valid check if the space has food
	//if it has food-->update food && update body
	//make movement
	//update head position
	//use fkey(fault key) to check the wrong direction
    int i;
    
    if(snake.head.pos.x<=1 or snake.head.pos.x >= ROW+1 or snake.head.pos.y <=0 or snake.head.pos.y >=COL) //checks if the head reaches the boundary
    {
        end();
    }
    for(i = 0; i<snake.body.count();i++){
       if(snake.head.pos.x == snake.body.body_[i].x and snake.head.pos.y == snake.body.body_[i].y) //checks if the snake hit itself
       {
           end();
       }
       }
        if(snake.head.pos.x == food.pos.x and snake.head.pos.y == food.pos.y){//this is where the snake eats food, and makes the body bigger
            food.update(snake.body.body_,snake.head.pos.x,snake.head.pos.y);
            snake.body.add(0,0);
            score++;

        }
        
	snake.body.move(snake.head.pos.x,snake.head.pos.y);
	switch(snake.head.direction) //this is for controlling the snake
    {
		case UP:
		if (fkey!='d'){
			snake.head.pos.x-=1;
			fkey='u';
			}
		else{
			snake.head.pos.x+=1;
			}
		break;
		case DOWN: 
			if (fkey!='u'){
			snake.head.pos.x+=1;
			fkey='d';
			}
		else{
			snake.head.pos.x-=1;
			}
		break;
		case RIGHT:
			if (fkey!='l'){
			snake.head.pos.y+=1;
			fkey='r';
			}
		else{
			snake.head.pos.y-=1;
			}
		break;
		case LEFT:
			if (fkey!='r'){
			snake.head.pos.y-=1;
			fkey='l';
			}
		else{
			snake.head.pos.y+=1;
			}
		break;
		default:
		break;
    
    
    }
    
}

void Game::start(){
    int quit = 0;
    while(!quit)
    {
        system("stty -echo -icanon");   //cancel cache；
        pen.hide_cur();                     
        pen.clr_scrn();                     
        drawBox();
        //This designs the welcome page
        pen.goto_xy(6,33);
        pen.putstr(34, 1, "WELCOME TO SNAKE");
        pen.goto_xy(8,30);
        pen.putstr(34,1,"PRESS '1' FOR NEW GAME");
        pen.goto_xy(10,28);
        pen.putstr(34, 1, "PRESS '2' FOR INSTRUCTIONS");
        fflush(stdout); //flush the buffer
        int back = 0;
        
        while(!back)
        {
            char key = '0';
            int i;
            key = get_key();
            switch(key)
            {
                case 50: //This is for the instructions
                    pen.goto_xy(12,33);
                    pen.putstr(36,1,"DO: Eat food! ");
                    pen.goto_xy(14,26);
                    pen.putstr(36,1,"DON'T: Eat yourself or crash...");
                    fflush(stdout);
                    break;
                    
                case 49: //This starts the game
                gameStart();
                std::thread f1([&](){
                handler(); //This calls the handler
                });
                    std::thread f2([&](){
                        getKey();
                    });
                    f1.join();
                    f2.join();
 
                        back = 1; // note for end
                        break;
                    
            }
 
        }
    }
    end();// end of game
}


//Handler is use to draw food and update snake position
void Game::handler(){
    
    while(true){ //Infine loop
     drawBox();
     pen.draw_rect(food.pos.x, food.pos.y + 20, 1, 1, 46 , 36, '#');
     snakeMove();
     drawSnake();
     fflush(stdout);
     usleep(speed); //This controls the speed
    }
}


void Game::gameStart(){
    snake.head.pos.x = 10;//Initialize the head position
    snake.head.pos.y = 20; 
	snake.body.add(10,19);//Initialize the body position
	snake.body.add(10,18); 
	snake.body.add(10,17);
    fkey = 'r'; //This is the direction
    snake.head.direction = RIGHT;//This is the head direction
    speed=200000; //This updates the speed
    score=0; //Initialize the score
    nextLevel = 3; //Initialize the next level
    food.update(snake.body.body_,snake.head.pos.x,snake.head.pos.y); //Initialize the food position
}



