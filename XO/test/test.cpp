#include <iostream>

#include "BoardTest.h"
#include "Test.h"

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char  *filename, size_t lineNum) {
	totalNum++;
	if (expr == false) {
		failedNum++;
		std::cout << "Test " << func << " failed in " << filename << ": " << lineNum << '\n'; 
	}
}

bool Test::showFinalResult() {
	std::cout << "Passed " << totalNum - failedNum << " out of " << totalNum << " tests\n";
	if (failedNum == 0) {	
		return true;
	}
	return false;
}
