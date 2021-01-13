#include <iostream>
#include <conio.h>//input/output
#include <windows.h>
using namespace std;
bool gameOver;
//map size
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 0; //specifies the length of the tail
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //directional keys
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2; // x and y divided by two so its centered
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0; // initialize score to 0
}

void Draw() // draw out our map
{
	system("cls"); //clearing the board
	for (int i = 0; i < width + 2; i++) //top wall
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				cout << "#";
			}

			if (i == y && j == x)
			{
				cout << "O"; //head
			}

			else if (i == fruitY && j == fruitX)
			{
				cout << "F";//fruit
			}

			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++) //drawing our tail
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}

				if (!print)
				{
					cout << " ";
				}
			}

			if (j == width - 1)
			{
				cout << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)//bottom wall
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl; //displays score
}

void Input()
{
	if (_kbhit()) //keyboard inputs
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;

		case 'd':
			dir = RIGHT;
			break;

		case 'w':
			dir = UP;
			break;

		case 's':
			dir = DOWN;
			break;

		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x; //follows the head now
	tailY[0] = y;// follows the head now
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) //directions
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

	if (x > width || x < 0 || y > height || y < 0) //if outside boundaries, game terminates
	{
		gameOver = true;
	}

	for (int i = 0; i < nTail; i++) // if we run into our tail then we lose
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) //if our snake touches the fruit then ..
	{
		score += 10; // each fruit is 10 points
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++; //increases tail when we eat fruit
	}
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(100); //slows the game down
	}

	return 0;
}