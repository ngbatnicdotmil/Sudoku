#pragma once
#include <windows.h>
#include <vector>

#define BOARD_SIZE 9

using namespace std;

enum colors
{
	White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	LightGreen = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	LightRed = FOREGROUND_RED | FOREGROUND_INTENSITY,
	Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
};


class Sudoku {

public:
	void generate();
	void take(short);
	void display();
	void play();
	short diff();
	bool boardSolved();
private:
	vector <COORD> xy_cv;
	vector <COORD> xy;
	int boardArray[BOARD_SIZE][BOARD_SIZE];
};