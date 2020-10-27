#include <iostream>

#include "BoardTest.h"
#include "Test.h"

int main() {
	BoardTest bt;
	bt.runAllTests();
	Test::showFinalResult();
	return 0;
}
