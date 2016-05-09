#include "Sudoku.h"

int main() {
	Sudoku s1;

	s1.generate();
	s1.take(s1.diff());
	s1.display();
	s1.play();

	return 0;
}
