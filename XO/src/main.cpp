#include <iostream>
#include <cstring>

#include "Board.h"
#include "StdioBoardView.h"

int main(int args, char **argv) {
	bool silent = false;
	if (args > 1 && strcmp(argv[1], "silent") == 0) {
		silent = true;
	}
	Board board;
	StdioBoardView view(board, silent);
	view.runGame();
	return 0;
}
