// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//
// ConsoleApplication3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define ROWS 20
#define COLS 50
#define SNAKEMAXSIZE	1000

bool bEndGame = false;

char map[ROWS][COLS];
char maprun[ROWS][COLS];
int Snake[SNAKEMAXSIZE][2];
int head = 0;
int tail = 0;

enum DIRECTION {
	LEFT, RIGHT, UP, DOWN
}direct;

struct Food
{
	int x;
	int y;
	int isEaten;
}food;

void CreateMap()
{
	int x, y;
	for (y = 0; y < ROWS; y++)
	{
		for (x = 0; x < COLS; x++)
		{
			if (y == 0 || y == ROWS - 1 || x == 0 || x == COLS - 1) {
				map[y][x] = '#';
			}
			else {
				map[y][x] = ' ';
			}
		}
	}

}
void CreateSnake()
{
	int x, y;
	x = 10;
	y = 10;
	Snake[tail][0] = x;
	Snake[tail][1] = y;
	tail++;
	direct = RIGHT;

}
void SnakeRun()
{
	int newhead = head - 1;
	if (newhead < 0) {
		newhead = SNAKEMAXSIZE - 1;
	}
	Snake[newhead][0] = Snake[head][0];
	Snake[newhead][1] = Snake[head][1];
	switch (direct) {
	case LEFT:
		Snake[newhead][0]--;
		if (Snake[newhead][0] <= 0) {
			Snake[newhead][0] = COLS - 2;
		}
		break;
	case RIGHT:
		Snake[newhead][0]++;
		if (Snake[newhead][0] >= COLS - 1) {
			Snake[newhead][0] = 1;
		}
		break;
	case UP:
		Snake[newhead][1]--;
		if (Snake[newhead][1] <= 0) {
			Snake[newhead][1] = ROWS - 2;
		}
		break;
	case DOWN:
		Snake[newhead][1]++;
		if (Snake[newhead][1] >= ROWS - 1) {
			Snake[newhead][1] = 1;
		}
		break;
	}
	head = newhead;
	if (Snake[head][0] == food.x && Snake[head][1] == food.y) {
		food.isEaten = true;
	}
	else {

		tail = tail - 1;
		if (tail < 0) {
			tail = SNAKEMAXSIZE - 1;
		}
	}

}
void ControlAndRun()
{
	int key;
	if (_kbhit()) {
		key = _getch();
		switch (key) {
		case 'a':
			direct = LEFT;
			break;
		case 's':
			direct = DOWN;
			break;
		case 'd':
			direct = RIGHT;
			break;
		case 'w':
			direct = UP;
			break;
		case 27:
			bEndGame = true;
			break;
		}

	}

	SnakeRun();


}
bool isSnake(int x, int y)
{
	int i = head;
	do {
		if (Snake[i][0] == x && Snake[i][1] == y) {
			return true;
		}
		i++;
		if (i == SNAKEMAXSIZE) {
			i = 0;
		}
	} while (i != tail);
	return false;
}
void CreateFood()
{
	if (food.isEaten)
	{
		food.x = rand() % (COLS - 2) + 1;
		food.y = rand() % (ROWS - 2) + 1;
		food.isEaten = 0;

		do
		{
			if (isSnake(food.x, food.y))
			{
				food.x = rand() % (COLS - 2) + 1;
				food.y = rand() % (ROWS - 2) + 1;
			}
		} while (isSnake(food.x, food.y));
	}
}

void Gotoxy(int column, int row)
{
	COORD c;

	c.X = column;
	c.Y = row;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void Visualize()
{

	int x, y;


	for (y = 0; y < ROWS; y++)
	{
		for (x = 0; x < COLS; x++)
		{
			maprun[y][x] = map[y][x];
		}
	}
	maprun[food.y][food.x] = '$';


	int i = head;
	do {

		maprun[Snake[i][1]][Snake[i][0]] = 'o';
		i++;
		if (i == SNAKEMAXSIZE) {
			i = 0;
		}
	} while (i != tail);

	Gotoxy(0, 0);
	for (y = 0; y < ROWS; y++)
	{
		for (x = 0; x < COLS; x++)
		{
			printf("%c", maprun[y][x]);
		}

		printf("\n");
	}

}

void noCursor()
{
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = FALSE;
	cci.dwSize = sizeof(cci);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cci);
}


int main()
{

	int gamespeed = 100;

	noCursor();

	srand(time(NULL));

	food.isEaten = true;


	CreateMap();
	CreateSnake();

	do
	{
		CreateFood();
		Visualize();
		Sleep(gamespeed);
		//system("CLS");
		ControlAndRun();

	} while (!bEndGame);

	return 0;
}

