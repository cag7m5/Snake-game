#include <iostream>
#include <conio.h>
#include <windows.h>
#define KEY_UP 72 
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13
using namespace std;
bool gameEnd;
const int boardWidth = 20;
const int boardHeight = 20;
enum direction {STOP, UP, DOWN, LEFT, RIGHT};
direction direct;
int score, headX, headY, coinX, coinY, tailLength;
int tailX[200], tailY[200];


void setup() {//default setup for the screen
	gameEnd = false;
	score = 0;
	direct = STOP;
	headX = boardWidth/2;
	headY = boardHeight/2;
	coinX = rand() % boardWidth;
	coinY = rand() % boardHeight;


}
void screen() {//displays everything
	system("cls");
	for (int i = 0;i < boardWidth;i++)
		cout << "-";
	cout << endl;
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			if (j == 0||j==boardWidth-1)
				cout << "|";
			else if (i == headY && j == headX)
				cout << "O";
			else if (i == coinY && j == coinX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < tailLength; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < boardWidth; i++)
		cout << "-";
	cout << endl << endl;
	cout << "Score:" << score << endl;
}


void controls() {

	if (_kbhit()) {//each button hit 
		switch (_getch()) {
		case KEY_UP:
			direct = UP;
			break;
		case KEY_DOWN:
			direct = DOWN;
			break;
		case KEY_LEFT:
			direct = LEFT;
			break;
		case KEY_RIGHT:
			direct = RIGHT;
			break;
		case ENTER:
			gameEnd = true;
			break;
		}
	}


}
void gameLogic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = headX;
	tailY[0] = headY;
	for (int i = 1; i < tailLength; i++)//this loop allows the tail to follow the head by remembering its previous position temporarily
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (direct)//how the snake moves for each control
	{
	case UP:
		headY--;
		break;
	case DOWN:
		headY++;
		break;
	case LEFT:
		headX--;
		break;
	case RIGHT:
		headX++;
		break;
	default:
		break;
	}

	if (headX > boardWidth+1 || headX<0 || headY>boardHeight+1|| headY < 0)gameEnd = true;//ends game if the wall is touched
	for (int i = 0;i < tailLength;i++) {//if the head hits the tail, game ends
		if (tailX[i] == headX && tailY[i] == headY)
			gameEnd = true;
	}
	if (headX == coinX && headY == coinY) {//resets coin if caught and adds score
		score += 100;
		tailLength++;
		coinX = rand() % boardWidth;
		coinY = rand() % boardHeight;
	}

}
int main() {
	setup();
	while (!gameEnd) {
		screen();
		controls();
		gameLogic();
		Sleep(50);
	}
	return 0;
}
