#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;  // x,y is position of snake
int tailX[100], tailY[100];       //tail of snake increases
int nTail;                        //length of tail
enum eDirection{STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
void SetUp()
{
    gameOver=false;
    dir = STOP;
     x = width/2;
     y = height/2;
     fruitX = rand()%width;
     fruitY = rand()%height;
     score = 0;
}
void Draw()             //Draw map
{
    system("cls");
    for(int i=0;i<width+2;i++)                   //TOP line of map
        cout<<"#";
    cout<<endl;

    for(int i=0;i<height;i++)                   //sides of map
    {
        for(int j=0;j<width;j++)               //sides of map
        {
            if(j==0)
                cout<<"#";                    //left end
            if(i==y&& j==x)
                cout<<"O";                   //Position snake in middle
            else if(i==fruitY && j==fruitX)
                cout<<"$";
            else
                {
                    bool print = false;
                    for(int k=0;k<nTail;k++)    //Loop for printing tail
                    {
                        if(tailX[k]==j && tailY[k]==i)
                        {
                            cout<<"o";
                            print = true;
                        }
                    }
                    if(!print)                  //if not  true , i.e if snake tail isn't to be printed
                        cout<<" ";
                }

            if (j== width-1)                 //right end
                cout<<"#";

        }
        cout<<endl;
    }

    for(int i=0;i<width+2;i++) //Bottom line of map
        cout<<"#";
    cout<<endl;
    cout<<" Score"<<score<<endl;


}
void Input()
{
    char key_hit;
    while(!kbhit())                 //waiting for keyboard hit
    {
    }
   // if(kbhit())



        key_hit = getch();  //getting which key is pressed
        switch(key_hit)  //for w , a, s ,d direction
        {
        case 'a':
            dir=LEFT;
            break;
        case 'd':
            dir=RIGHT;
            break;
        case 'w':
            dir=UP;
            break;
        case 's':
            dir=DOWN;
            break;
        case 'x':       //for gameOver press X
            gameOver=true;
            break;
        default:
            break;
        }



}
void Logic()
{
    int prevX = tailX[0];       //Previous tail X-coordinate
    int prevY = tailY[0];       //Previous tail Y-coordinate
    int prev2X, prev2Y;         //Previous 2 x,y-coordinate
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)     //we need this loop because after 2 values it wont be stored
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
    switch(dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
         x++;
         break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x > width || x < 0 || y > height || y < 0)              //FOR going out of map
	{
	   gameOver = true;
	   cout<<"You lost! :( "<<endl;
	   getch();
	}
	if(x==fruitX && y==fruitY)
    {

        score += 10;
        fruitX = rand()%width;
        fruitY = rand()%height;
        nTail++;
    }
}
int main()
{
    SetUp();
    while(!gameOver)
    {
        Draw();
        Input();
        Logic();
        //Sleep(10);
        //getch();
    }
    return 0;
}
