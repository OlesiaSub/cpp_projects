#pragma once

#include "Board.h"

class StdioBoardView {
public:
    StdioBoardView(Board &board, bool silent_ = false);

    void runGame();

	void sendBoard();

private:
	Board &view_;
	bool silent_ = false;
};
