#ifndef CELLTEST_H
#define CELLTEST_H

#include "Cell.h"

class CellTest {
private:
	Cell tester;
	unsigned int passingTests = 0;
	unsigned int failingTests = 0;
public:
	CellTest();

	// tests
	void runTests();
};

#endif