#include "Maze.h"

#include <iostream>

#include "Cell.h"

Maze::Maze(unsigned long long int width, unsigned long long int height, unsigned long long int cellPreset)
{
	if (width < 0)
		width = 1;
	if (height < 0)
		height = 1;
	this->width = width;
	this->height = height;
	this->mazePtr = new Cell[(width * height)];
	for (unsigned long long int i = 0; i < (width * height); i++) {
		this->mazePtr[i].setRaw(cellPreset);
	}
}

Maze::~Maze()
{
	delete this->mazePtr;
	this->mazePtr = nullptr;
}

unsigned long long int Maze::getWidth()
{
	return this->width;
}

unsigned long long int Maze::getHeight()
{
	return this->height;
}

unsigned long long int Maze::getCellIndex(unsigned long long int x, unsigned long long int y)
{
	if (x < 1)
		x = 1;
	if (y < 1)
		y = 1;
	return (this->width * (y - 1uLL)) + x - 1uLL; 
}

unsigned long long int Maze::getCellXCoord(unsigned long long int idx)
{
	if (idx < 0)
		idx = 0;
	return (idx % this->width) + 1uL;
}

unsigned long long int Maze::getCellYCoord(unsigned long long int idx)
{
	if (idx < 0)
		idx = 0;
	return (idx / this->width) + 1uL;
}
