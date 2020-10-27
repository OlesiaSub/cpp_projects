#include <iostream>

#include "Board.h"
#include "StdioBoardView.h"
#include "BoardTest.h"
#include "Test.h"

#define SIZE 10

void BoardTest::testCanMove1() {
	Board board;
	board.move(5, 7, EMPTY, EMPTY);
	DO_CHECK(board.canMove(5, 6, EMPTY, EMPTY) == true);
}

void BoardTest::testCanMove2() {
	Board board;
	board.move(0, 1, EMPTY, EMPTY);
	DO_CHECK(board.canMove(0, 1, EMPTY, EMPTY) == true);
}

void BoardTest::testCanMove3() {
	Board board;
	board.move(2, 3, X_PLACED, X_PLACED);
	DO_CHECK(board.canMove(2, 3, X_PLACED, X_PLACED) == false);
}

void BoardTest::testCanNotMoveO() {
	Board board;
	board.move(1, 4, O_PLACED, X_PLACED);
	DO_CHECK(board.canMove(1, 4, O_PLACED, X_PLACED) == false);
}

void BoardTest::testCanNotMoveX() {
	Board board;
	board.move(6, 7, X_PLACED, O_PLACED);
	DO_CHECK(board.canMove(6, 7, X_PLACED, O_PLACED) == false);
}

void BoardTest::testMoveO1() {
	Board board;
	board.move(3, 1, O_PLACED, X_PLACED);
	DO_CHECK(board.getBoard(3, 1) == O_PLACED);
}

void BoardTest::testMoveO2() {
	Board board;
	board.move(0, 5, O_PLACED, X_PLACED);
	DO_CHECK(board.getBoard(0, 5) == O_PLACED);
}

void BoardTest::testMoveX1() {
	Board board;
	board.move(1, 1, X_PLACED, O_PLACED);
	DO_CHECK(board.getBoard(1, 1) == X_PLACED);
}	

void BoardTest::testMoveX2() {
	Board board;
	board.move(1, 9, X_PLACED, O_PLACED);
	DO_CHECK(board.getBoard(1, 9) == X_PLACED);
}

void BoardTest::testProcess() {
	Board board;
	board.move(7, 8, O_PLACED, X_PLACED);
	board.move(1, 4, X_PLACED, O_PLACED);
	board.move(0, 1, O_PLACED, X_PLACED);
	board.move(2, 1, X_PLACED, O_PLACED);
	DO_CHECK(board.getState() == PROCESS);
}

void BoardTest::testWinX_vert() {
	Board board;
	board.move(7, 8, O_PLACED, X_PLACED);
	board.move(1, 0, X_PLACED, O_PLACED);
	board.move(0, 8, O_PLACED, X_PLACED);
	board.move(2, 0, X_PLACED, O_PLACED);
	board.move(7, 4, O_PLACED, X_PLACED);
	board.move(3, 0, X_PLACED, O_PLACED);
	board.move(5, 3, O_PLACED, X_PLACED);
	board.move(4, 0, X_PLACED, O_PLACED);
	board.move(0, 0, X_PLACED, O_PLACED);
	DO_CHECK(board.getState() == X_WINS);
}

void BoardTest::testWinO_hor() {
	Board board;
	board.move(0, 0, O_PLACED, X_PLACED);
	board.move(1, 0, X_PLACED, O_PLACED);
	board.move(0, 1, O_PLACED, X_PLACED);
	board.move(5, 0, X_PLACED, O_PLACED);
	board.move(0, 4, O_PLACED, X_PLACED);
	board.move(3, 0, X_PLACED, O_PLACED);
	board.move(0, 3, O_PLACED, X_PLACED);
	board.move(4, 0, X_PLACED, O_PLACED);
	board.move(0, 2, O_PLACED, X_PLACED);
	DO_CHECK(board.getState() == O_WINS);
}

void BoardTest::testWinO_slash() {
	Board board;
	board.move(9, 2, O_PLACED, X_PLACED);
	board.move(5, 2, X_PLACED, O_PLACED);
	board.move(8, 3, O_PLACED, X_PLACED);
	board.move(9, 6, X_PLACED, O_PLACED);
	board.move(7, 4, O_PLACED, X_PLACED);
	board.move(8, 2, X_PLACED, O_PLACED);
	board.move(5, 6, O_PLACED, X_PLACED);
	board.move(4, 4, X_PLACED, O_PLACED);
	board.move(6, 5, O_PLACED, X_PLACED);
	DO_CHECK(board.getState() == O_WINS);
}

void BoardTest::testWinX_slash() {
	Board board;
	board.move(6, 0, O_PLACED, X_PLACED);
	board.move(1, 1, X_PLACED, O_PLACED);
	board.move(4, 1, O_PLACED, X_PLACED);
	board.move(3, 3, X_PLACED, O_PLACED);
	board.move(0, 4, O_PLACED, X_PLACED);
	board.move(2, 2, X_PLACED, O_PLACED);
	board.move(0, 8, O_PLACED, X_PLACED);
	board.move(4, 4, X_PLACED, O_PLACED);
	board.move(0, 2, O_PLACED, X_PLACED);
	board.move(0, 0, X_PLACED, O_PLACED);
	DO_CHECK(board.getState() == X_WINS);
}

void BoardTest::testWinO_backslash() {
	Board board;
	board.move(0, 9, O_PLACED, X_PLACED);
	board.move(1, 3, X_PLACED, O_PLACED);
	board.move(1, 8, O_PLACED, X_PLACED);
	board.move(9, 6, X_PLACED, O_PLACED);
	board.move(2, 7, O_PLACED, X_PLACED);
	board.move(8, 2, X_PLACED, O_PLACED);
	board.move(3, 6, O_PLACED, X_PLACED);
	board.move(4, 4, X_PLACED, O_PLACED);
	board.move(4, 5, O_PLACED, X_PLACED);
	DO_CHECK(board.getState() == O_WINS);
}

void BoardTest::testWinX_backslash() {
	Board board;
	board.move(6, 9, O_PLACED, X_PLACED);
	board.move(1, 9, X_PLACED, O_PLACED);
	board.move(1, 8, O_PLACED, X_PLACED);
	board.move(3, 7, X_PLACED, O_PLACED);
	board.move(2, 7, O_PLACED, X_PLACED);
	board.move(2, 8, X_PLACED, O_PLACED);
	board.move(1, 6, O_PLACED, X_PLACED);
	board.move(5, 5, X_PLACED, O_PLACED);
	board.move(0, 3, O_PLACED, X_PLACED);
	board.move(4, 6, X_PLACED, O_PLACED);
	DO_CHECK(board.getState() == X_WINS);
}

void BoardTest::testDraw() {
	Board board;
	int cnt = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cnt++;
			if (cnt % 4 == 0 || cnt % 4 == 1) {
				board.move(i, j, O_PLACED, X_PLACED);
			}
			if (cnt % 4 == 2 || cnt % 4 == 3) {
				board.move(i, j, X_PLACED, O_PLACED);
			}
		}
	}
	DO_CHECK(board.getState() == DRAW);
}
