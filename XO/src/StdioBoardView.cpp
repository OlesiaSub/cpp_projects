#include <iostream>

#include "StdioBoardView.h"

#define SIZE 10

StdioBoardView::StdioBoardView(Board &view_, bool silent_) : view_(view_), silent_(silent_) {}

void StdioBoardView::sendBoard() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			std::cout << view_.getBoard(i, j);
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void StdioBoardView::runGame() {
	cell_sign cur = O_PLACED;
	cell_sign prev = X_PLACED;
	int x, y;
	//string s;
	while (view_.getState() == PROCESS) {
		if (silent_ == false) sendBoard();
		while (1) {
			std::cout << (char)cur << " move: ";
			std::cin >> x >> y;
			if ((x == -1 && y == -1) || view_.canMove(x, y, cur, prev) == true) {
				break;
			} else {
				std::cout << "Bad move!" << std::endl;
			}
		}
		if (x == -1 && y == -1) {
			break;
		}
		view_.move(x, y, cur, prev);
		prev = cur;
		cur == X_PLACED ? cur = O_PLACED : cur = X_PLACED;
		std::cout << std::endl;
	}
	game_state state = view_.getState();
	if (state == O_WINS) {
		sendBoard();
		std::cout << "O wins!" << std::endl;
		state = PROCESS;
	}
	if (state == X_WINS) {
		sendBoard();
		std::cout << "X wins!" << std::endl;
		state = PROCESS;
	}
	if (state == DRAW) {
		sendBoard();
		std::cout << "Draw." << std::endl;
		state = PROCESS;
	}
}
