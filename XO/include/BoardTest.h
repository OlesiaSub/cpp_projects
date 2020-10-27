#pragma once

#include <iostream>

#include "Test.h"

#define DO_CHECK(EXPR) BoardTest::check(EXPR, __func__, __FILE__, __LINE__);

class BoardTest : public Test {
private:
	void testCanMove1();
	void testCanMove2();
	void testCanMove3();
	void testCanNotMoveO();
	void testCanNotMoveX();
	void testMoveX1();
    void testMoveX2();
	void testMoveO1();
    void testMoveO2();
	void testProcess(); 
    void testWinX_vert();
	void testWinO_hor();
	void testWinO_slash();
	void testWinX_slash();
	void testWinO_backslash();
	void testWinX_backslash();
	void testDraw();
    
public:
    void runAllTests() {
		testCanMove1();
		testCanMove2();
		testCanMove3();
		testCanNotMoveO();
		testCanNotMoveX();
		testMoveX1();
		testMoveX2();
		testMoveO1();
		testMoveO2();
		testProcess(); 
        testWinX_vert();
		testWinO_hor();
		testWinO_slash();
		testWinX_slash();
		testWinO_backslash();
		testWinX_backslash();
		testDraw();
    }
};
