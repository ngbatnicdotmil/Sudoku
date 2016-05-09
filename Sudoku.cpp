#include "Sudoku.h"
#include <time.h>
#include <conio.h>
#include <iostream>


HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void Sudoku::generate() {
	srand(static_cast<int>(time(NULL)));
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			boardArray[i][j] = j + ((i / 3) + 3 * (i % 3)) + 1;
			if (boardArray[i][j] > 9) {
				boardArray[i][j] = boardArray[i][j] - 9;
			}
		}
	}


	int numSwaps = rand() % 500;

	while (numSwaps > 0) {
		int num1 = rand() % 9 + 1;
		int num2 = rand() % 9 + 1;

		if (num1 != num2) {
			numSwaps--;

			for (int i = 0; i < BOARD_SIZE; i++) {
				for (int j = 0; j < BOARD_SIZE; j++) {

					if (boardArray[i][j] == num1) {
						boardArray[i][j] = num2;
					}
					else if (boardArray[i][j] == num2) {
						boardArray[i][j] = num1;
					}
					else
						continue;
				}
			}
		}
	}


	int rowSwaps = rand() % 500;

	while (rowSwaps > 0) {
		int row1Pos = rand() % 9 + 1;
		int row2Pos = rand() % 9 + 1;

		if (((row1Pos / 3) == (row2Pos / 3)) && (row1Pos != row2Pos)) {
			int row1[BOARD_SIZE];
			int row2[BOARD_SIZE];

			for (int i = 0; i < BOARD_SIZE; i++) {
				row1[i] = boardArray[row1Pos][i];
				row2[i] = boardArray[row2Pos][i];
			}
			rowSwaps--;
			for (int i = 0; i < BOARD_SIZE; i++) {
				boardArray[row1Pos][i] = row2[i];
				boardArray[row2Pos][i] = row1[i];
			}
		}
	}


	int colSwaps = rand() % 500;

	while (colSwaps > 0) {
		int col1Pos = rand() % 9 + 1;
		int col2Pos = rand() % 9 + 1;

		if (((col1Pos / 3) == (col2Pos / 3)) && (col1Pos != col2Pos)) {
			int col1[BOARD_SIZE];
			int col2[BOARD_SIZE];

			for (int i = 0; i < BOARD_SIZE; i++) {
				col1[i] = boardArray[i][col1Pos];
				col2[i] = boardArray[i][col2Pos];
				colSwaps--;
				for (int i = 0; i < BOARD_SIZE; i++) {
				}
				boardArray[i][col1Pos] = col2[i];
				boardArray[i][col2Pos] = col1[i];
			}
		}
	}

}



void Sudoku::display() {
	system("cls");

	SetConsoleTextAttribute(h, Yellow);
	cout << "Left/Right ";
	SetConsoleTextAttribute(h, White);
	cout << "to select a cell" << endl;
	SetConsoleTextAttribute(h, Yellow);
	cout << "UP/DOWN, 1-9 ";
	SetConsoleTextAttribute(h, White);
	cout << "to change the number in the cell" << endl;
	SetConsoleTextAttribute(h, Yellow);
	cout << "ENTER ";
	SetConsoleTextAttribute(h, White);
	cout << "to check" << endl;
	SetConsoleTextAttribute(h, Yellow);
	cout << "SPACE ";
	SetConsoleTextAttribute(h, White);
	cout << "to start a new game" << endl << endl;

	for (int i = 0; i < BOARD_SIZE; i++) {

		for (int j = 0; j < BOARD_SIZE; j++) {

			if (j > 0 && j % 3 == 0) {
				cout << "| ";
			}
			if (i > 0 && i % 3 == 0 && j == 0) {
				cout << "---------------------" << endl;
			}
			if (boardArray[i][j] == 0) {

				CONSOLE_SCREEN_BUFFER_INFO SBInfo;
				GetConsoleScreenBufferInfo(h, &SBInfo);
			
				xy_cv.push_back(SBInfo.dwCursorPosition);

				SetConsoleTextAttribute(h, Yellow);
				cout << "_ ";
				SetConsoleTextAttribute(h, White);
			}
			else {
				cout << boardArray[i][j] << " ";
			}
		}
		cout << endl;
	}
}


bool Sudoku::boardSolved() {

	bool kFound = false;

	for (int k = 1; k < 10; k++) {
		for (int i = 0; i < BOARD_SIZE; i++) {
			kFound = false;
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (boardArray[i][j] == k) {
					kFound = true;
				}
			}
			if (!kFound) {
				return false;
			}
		}
	}

	for (int k = 1; k < 10; k++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			kFound = false;
			for (int i = 0; i < BOARD_SIZE; i++) {
				if (boardArray[i][j] == k) {
					kFound = true;
				}
			}
			if (!kFound) {
				return false;
			}
		}
	}
	return true;
}


void Sudoku::take(short t) {

	COORD tmp;
	while (t > 0) {	
		int randomX = rand() % 9;
		int randomY = rand() % 9;
		if (boardArray[randomX][randomY] != 0) {
			boardArray[randomX][randomY] = 0;

			tmp.X = randomX;
			tmp.Y = randomY;
			xy.push_back(tmp);

			t--;
		}
	}
}


void Sudoku::play() {

	int c;
	int pos = 0;
	while (true) {
		SetConsoleTextAttribute(h, Yellow);
		SetConsoleCursorPosition(h, xy_cv.at(pos));

		switch ((c = _getch())) {
		case 72: // UP
			if (boardArray[xy.at(pos).X][xy.at(pos).Y] < 9)
				boardArray[xy.at(pos).X][xy.at(pos).Y]++;
			else
				boardArray[xy.at(pos).X][xy.at(pos).Y] = 1;
				cout << boardArray[xy.at(pos).X][xy.at(pos).Y];
			break;
		case 80: // DOWN
			if (boardArray[xy.at(pos).X][xy.at(pos).Y] > 1)
				boardArray[xy.at(pos).X][xy.at(pos).Y]--;
			else
				boardArray[xy.at(pos).X][xy.at(pos).Y] = 9;
				cout << boardArray[xy.at(pos).X][xy.at(pos).Y];
			break;
		case 75: // LEFT
			if (pos == 0)
				pos = xy_cv.size() - 1;
			else
				pos--;
			break;
		case 77: // RIGHT
			if (pos == xy_cv.size() - 1)
				pos = 0;
			else
				pos++;
			break;
		case ' ': // SPACE
			system("cls");
			xy.clear();
			xy_cv.clear();

			generate();
			take(diff());
			display();
			play();
			break;
		case 13: // ENTER
			if (boardSolved()) {
				system("cls");
				SetConsoleTextAttribute(h, LightGreen);
				cout << "Congratulations! You solved the puzzle";
				Sleep(1000);
				exit(0);
			}
			else {
				COORD tmp = { 0,16 };

				SetConsoleCursorPosition(h, tmp);
				SetConsoleTextAttribute(h, LightRed);
				cout << "Try harder";
				Sleep(500);
				cout << "\r          ";
			}
			break;
		case 27: // ESCAPE
			exit(0);
			break;
		default: // nums
			if (c >= 49 && c <= 57) {
				cout << c - 48;
				boardArray[xy.at(pos).X][xy.at(pos).Y] = c - 48;
			}
			break;
		}
	}
}

short Sudoku::diff() {

	SetConsoleTextAttribute(h, White);
	cout << "Select difficulty: ";
	SetConsoleTextAttribute(h, Yellow);
	cout << "1-3";

	int c = 0;
	while (true) {
		switch ((c = _getch())) {
		case 48: // 0
			return 1;
			break;
		case 49: // 1
			return 10;
			break;
		case 50: // 2
			return 20;
			break;
		case 51: // 3
			return 30;
			break;
		}
	}
}
