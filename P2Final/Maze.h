#ifndef MAZE_H
#define MAZE_H

#include "Cell.h"

class Maze {
	private: 
		unsigned long long int width;
		unsigned long long int height;

	public: 
		Cell* mazePtr = nullptr;
		Maze(unsigned long long int = 101, unsigned long long int = 101, unsigned long long int = 0x00000uLL);
		~Maze();

		unsigned long long int getWidth();
		unsigned long long int getHeight();
		unsigned long long int getCellIndex(unsigned long long int, unsigned long long int);
		unsigned long long int getCellXCoord(unsigned long long int);
		unsigned long long int getCellYCoord(unsigned long long int);
};

#endif