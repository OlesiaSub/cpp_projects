#include <iostream>
#include <string>

#include "Board.h"

/* Board */

Board::Board() {
	for (int i = 0; i < getSize(); i++) {
		for (int j = 0; j < getSize(); j++) {
			board_[i][j] = EMPTY;
		}
	}
}

void Board::move(int x, int y, cell_sign cur, cell_sign prev) {
	if (canMove(x, y, cur, prev) == true) {
		board_[x][y] = cur;
	}
}

bool Board::canMove(int x, int y, cell_sign cur, cell_sign prev) {
	if (board_[x][y] == EMPTY && x >= 0 && y >= 0 && x <= getSize() && y <= getSize()) {
		if ((cur == EMPTY && prev == EMPTY) || cur != prev) {
			return true;
		}
		return false;
	}
	return false;
}

game_state Board::getState() {
	cell_sign player = EMPTY;
	int cnt;

	/* horisontal */

	for (int i = 0; i < getSize(); i++) {
		cnt = 1;
		player = EMPTY;
		for (int j = 0; j < getSize(); j++) {
			if (player == EMPTY) {
				player = board_[i][j];
				continue;
			}
			if (player == board_[i][j] && board_[i][j] != EMPTY) {
				cnt++;
				if (cnt == getWin()) {
					if (player == X_PLACED) {
						return X_WINS;
					} else if (player == O_PLACED) {
						return O_WINS;
					}
				}
			} else {
				cnt = 1;
				player = board_[i][j];
			}
		}
	}
	
	/* vertical */

	for (int j = 0; j < getSize(); j++) {
		cnt = 1;
		player = EMPTY;
		for (int i = 0; i < getSize(); i++) {
			if (player == EMPTY) {
				player = board_[i][j];
				continue;
			}
			if (player == board_[i][j] && board_[i][j] != EMPTY) {
				cnt++;
				if (cnt == getWin()) {
					if (player == X_PLACED) {
						return X_WINS;
					} else if (player == O_PLACED) {
						return O_WINS;
					}
				}
			} else {
				cnt = 1;
				player = board_[i][j];
			}
		}
	}
	
	/* slash 1.0 */

	int k = 0;
	for (int i = getWin() - 1; i <= 2 * getSize() - getWin() - 1; i++) {
		cnt = 1;
		player = EMPTY;
		for (int j = 0; j <= i; j++) {
			k = i - j;
			if (player == EMPTY) {
				player = board_[j][k];
				continue;
			}
			if (player == board_[j][k] && board_[j][k] != EMPTY) {
				cnt++;
				if (cnt == getWin()) {
					if (player == X_PLACED) {
						return X_WINS;
					} else if (player == O_PLACED) {
						return O_WINS;
					}
				}
			} else {
				cnt = 1;
				player = board_[j][k];
			}
		}
	}

	/* slash 2.0 */
	
	int m = 0;
	for (int i = getWin() - 1; i <= 2 * getSize() - getWin() - 1; i++) {
		cnt = 1;
		player = EMPTY;
		for (int j = 0; j <= i; j++) {
			k = i - j;
			m = getSize() - 1 - j;
			if (player == EMPTY) {
				player = board_[k][m];
				continue;
			}
			if (player == board_[k][m] && board_[k][m] != EMPTY) {
				cnt++;
				if (cnt == getWin()) {
					if (player == X_PLACED) {
						return X_WINS;
					} else if (player == O_PLACED) {
						return O_WINS;
					}
				}
			} else {
				cnt = 1;
				player = board_[k][m];
			}	
		}
	}

	/* check draw */

	bool flag = true;
	for (int i = 0; i < getSize(); i++) {
		for (int j = 0; j < getSize(); j++) {
			if (board_[i][j] == EMPTY) {
				flag = false;
				break;
			}
		}	
	}
	return flag ? DRAW : PROCESS;
}
