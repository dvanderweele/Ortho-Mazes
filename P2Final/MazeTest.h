#ifndef MAZETEST_H
#define MAZETEST_H

#include "Maze.h"

class MazeTest {
	private: 
		unsigned int passingTests = 0;
		unsigned int failingTests = 0;
	public:
		MazeTest();

		void runTests();
};

#endif