#pragma once

enum game_state { PROCESS, X_WINS, O_WINS, DRAW };
enum cell_sign { EMPTY = '.', X_PLACED = 'X', O_PLACED = 'O' };

class Board {
public:
	Board();	
	                                  
    bool canMove(int x, int y, cell_sign cur, cell_sign prev);

    void move(int x, int y, cell_sign cur, cell_sign prev);

    game_state getState();

	inline int getSize() { 
		return size_; 
	}

	inline int getWin() { 
		return win_size_; 
	}

	inline char getBoard(int i, int j) {
		return (char)board_[i][j];
	}

private:
	int size_ = 10;
	int win_size_ = 5;
	cell_sign board_[10][10];
};
