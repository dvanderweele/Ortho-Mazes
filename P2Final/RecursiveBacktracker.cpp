#include "RecursiveBacktracker.h"

#include <cstdlib>
#include <random>
#include <iostream>

bool RecursiveBacktracker::generate()
{
	bool res = true;
	// let's calculate x and y coordinates for a random starting cell
	unsigned long long int cellX = this->randomInt(2, this->maze->getWidth());
	unsigned long long int cellY = this->randomInt(2, this->maze->getHeight());
	if (cellX % 2 != 0)
		cellX = cellX - 1;
	if (cellY % 2 != 0)
		cellY = cellY - 1;
	this->maze->mazePtr[this->maze->getCellIndex(cellX, cellY)].setCarved();
	this->stack.push_back(this->maze->getCellIndex(cellX, cellY));
	while (this->stack.size() > 0) {
		cellX = this->maze->getCellXCoord(this->stack.back());
		cellY = this->maze->getCellYCoord(this->stack.back());
		bool northValid;
		bool northCarved;
		bool eastValid;
		bool eastCarved;
		bool southValid;
		bool southCarved;
		bool westValid;
		bool westCarved;
		// check north neighbor
		if (this->maze->mazePtr[this->maze->getCellIndex(cellX,(cellY-1))].isMapBorder()) {
			// there is no canonical north neighbor
			northValid = false;
			northCarved = false;
		}
		else {
			// there is a canonical north neighbor
			if (this->maze->mazePtr[this->maze->getCellIndex(cellX, (cellY - 2))].isCanonical()
				&& this->maze->mazePtr[this->maze->getCellIndex(cellX, (cellY - 2))].isCarved()) {
				// north neighbor already carved
				northValid = true;
				northCarved = true;
			}
			else {
				// north neighbor not carved yet
				northValid = true;
				northCarved = false;
			}
		}
		// check east neighbor
		if (this->maze->mazePtr[this->maze->getCellIndex((cellX + 1), cellY)].isMapBorder()) {
			// there is no canonical east neighbor
			eastValid = false;
			eastCarved = false;
		}
		else {
			// there is a canonical east neighbor
			if (this->maze->mazePtr[this->maze->getCellIndex((cellX+2), cellY)].isCanonical()
				&& this->maze->mazePtr[this->maze->getCellIndex((cellX+2), cellY)].isCarved()) {
				// east neighbor already carved
				eastValid = true;
				eastCarved = true;
			}
			else {
				// east neighbor not carved yet
				eastValid = true;
				eastCarved = false;
			}
		}
		// check south neighbor
		if (this->maze->mazePtr[this->maze->getCellIndex(cellX, (cellY + 1))].isMapBorder()) {
			// there is no canonical south neighbor
			southValid = false;
			southCarved = false;
		}
		else {
			// there is a canonical south neighbor
			if (this->maze->mazePtr[this->maze->getCellIndex(cellX, (cellY + 2))].isCanonical()
				&& this->maze->mazePtr[this->maze->getCellIndex(cellX, (cellY + 2))].isCarved()) {
				// south neighbor already carved
				southValid = true;
				southCarved = true;
			}
			else {
				// south neighbor not carved yet
				southValid = true;
				southCarved = false;
			}
		}
		// check west neighbor
		if (this->maze->mazePtr[this->maze->getCellIndex((cellX - 1), cellY)].isMapBorder()) {
			// there is no canonical west neighbor
			westValid = false;
			westCarved = false;
		}
		else {
			// there is a canonical west neighbor
			if (this->maze->mazePtr[this->maze->getCellIndex((cellX - 2), cellY)].isCanonical()
				&& this->maze->mazePtr[this->maze->getCellIndex((cellX - 2), cellY)].isCarved()) {
				// west neighbor already carved
				westValid = true;
				westCarved = true;
			}
			else {
				// west neighbor not carved yet
				westValid = true;
				westCarved = false;
			}
		}
		/*
			The stack will continue to grow in size until we reach a dead end. Then, in each
			subsequent iteration of the while loop a cell index will be popped off the end of
			the stack and so on and so forth until all the maze is finished.

			We first need to see if we've reached such a dead end, which really just means 
			that for the current cell, all four cardinal neighbors are either invalid 
			(i.e. map border cells) or already carved.
		*/
		if ((!northValid || northCarved) && (!eastValid || eastCarved) && (!southValid || southCarved) && (!westValid || westCarved)) {
			// reached a dead end, pop a cell off the stack
			this->stack.pop_back();
		}
		else {
			// one of the neighbors can be carved
			// collect our options from the set of our cardinal neighbors, separating them horizontally/vertically so we can use bias
			std::vector<int> hoptions;
			std::vector<int> voptions;
			if (northValid && !northCarved)
				voptions.push_back(1);
			if (southValid && !southCarved)
				voptions.push_back(3);
			if (eastValid && !eastCarved)
				hoptions.push_back(2);
			if (westValid && !westCarved)
				hoptions.push_back(4);
			// randomly decide horizontal or vertical according to bias if horizontal and vertical options both exist
			if (hoptions.size() > 0 && voptions.size() > 0) {
				// we must choose randomly according to bias
				if (this->randomFloat() > this->bias) {
					// pick from vertical list
					if (voptions.size() == 1) {
						// only one option
						switch (voptions[0]) {
						case 1: // north
							this->carveNorth(cellX, cellY);
							break;
						case 3: // south
							this->carveSouth(cellX, cellY);
							break;
						}
					}
					else {
						// randomly pick between two options
						if (this->randomFloat() > .5) {
							// pick first option
							switch (voptions[0]) {
							case 1: // north
								this->carveNorth(cellX, cellY);
								break;
							case 3: // south
								this->carveSouth(cellX, cellY);
								break;
							}
						}
						else {
							// pick second option
							switch (voptions[1]) {
							case 1: // north
								this->carveNorth(cellX, cellY);
								break;
							case 3: // south
								this->carveSouth(cellX, cellY);
								break;
							}
						}
					}
				}
				else {
					// pick from horizontal list
					if (hoptions.size() == 1) {
						// only one option
						switch (hoptions[0]) {
						case 2: // east
							this->carveEast(cellX, cellY);
							break;
						case 4: // west
							this->carveWest(cellX, cellY);
							break;
						}
					}
					else {
						// randomly pick between two options
						if (this->randomFloat() > .5) {
							// pick first option
							switch (hoptions[0]) {
							case 2: // east
								this->carveEast(cellX, cellY);
								break;
							case 4: // west
								this->carveWest(cellX, cellY);
								break;
							}
						}
						else {
							// pick second option
							switch (hoptions[1]) {
							case 2: // east
								this->carveEast(cellX, cellY);
								break;
							case 4: // west
								this->carveWest(cellX, cellY);
								break;
							}
						}
					}
				}
			}
			else {
				if (hoptions.size() > 0) {
					// we must choose from hoptions
					if (hoptions.size() == 1) {
						// only one option
						switch (hoptions[0]) {
						case 2: // east
							this->carveEast(cellX, cellY);
							break;
						case 4: // west
							this->carveWest(cellX, cellY);
							break;
						}
					}
					else {
						// randomly pick between two options
						if (this->randomFloat() > .5) {
							// pick first option
							switch (hoptions[0]) {
							case 2: // east
								this->carveEast(cellX, cellY);
								break;
							case 4: // west
								this->carveWest(cellX, cellY);
								break;
							}
						}
						else {
							// pick second option
							switch (hoptions[1]) {
							case 2: // east
								this->carveEast(cellX, cellY);
								break;
							case 4: // west
								this->carveWest(cellX, cellY);
								break;
							}
						}
					}
				}
				else {
					// we must choose from voptions
					if (voptions.size() == 1) {
						// only one option
						switch (voptions[0]) {
						case 1: // north
							this->carveNorth(cellX, cellY);
							break;
						case 3: // south
							this->carveSouth(cellX, cellY);
							break;
						}
					}
					else {
						// randomly pick between two options
						if (this->randomFloat() > .5) {
							// pick first option
							switch (voptions[0]) {
							case 1: // north
								this->carveNorth(cellX, cellY);
								break;
							case 3: // south
								this->carveSouth(cellX, cellY);
								break;
							}
						}
						else {
							// pick second option
							switch (voptions[1]) {
							case 1: // north
								this->carveNorth(cellX, cellY);
								break;
							case 3: // south
								this->carveSouth(cellX, cellY);
								break;
							}
						}
					}
				}
			}
		}
		if (this->randomFloat() < this->invertBiasChance) {
			this->bias = 1.0f - this->bias;
		}
	}
	if (prefersLoops) {
		this->carveSomeLoops();
	}
	return res;
}

/*
	This setup() function is to prep the maze grid by setting the starting 
	cell states. It isn't really appropriate to do this setup universally 
	in the Maze class because different generation algorithms have different 
	opinions on these starting qualities. So we set the "canonical cells" 
	and the other qualities algorithmically before we start the main part 
	of the procedural generation in the generate() function. Also, this 
	function picks random valid entry and exit cells.
*/
bool RecursiveBacktracker::setup()
{
	bool res = true;
	unsigned long long int cellX;
	unsigned long long int cellY;
	for (unsigned long long int i = 0; i < (this->maze->getWidth() * this->maze->getHeight()); i++) {
		cellX = this->maze->getCellXCoord(i);
		cellY = this->maze->getCellYCoord(i);
		if (cellY == 1								// top row
			|| cellY == this->maze->getHeight()		// bottom row
			|| cellX == 1							// left column
			|| cellX == this->maze->getWidth()) {	// right column
			this->maze->mazePtr[i].setMapBorder();
			this->maze->mazePtr[i].unsetCarved();
		}
		else {
			if (cellX % 2 == 0 && cellY % 2 == 0) {
				this->maze->mazePtr[i].setCanonical();
			}
			else {
				if (cellX % 2 == 0) {
					this->maze->mazePtr[i].setVertNeighbor();
				}
				else if (cellY % 2 == 0) {
					this->maze->mazePtr[i].setHorzNeighbor();
				}
				else {
					this->maze->mazePtr[i].setDiagNeighbor();
				}
			}
		}
	}
	unsigned long long int sidx, eidx, sx, sy, ex, ey;
	// pick random entry cell
	switch (this->startEdge) {
	case 0:
		sx = this->randomInt(2, this->maze->getWidth());
		if (sx % 2 != 0)
			sx = sx - 1;
		sidx = this->maze->getCellIndex(sx, 1);
		this->maze->mazePtr[sidx].setEntry();
		this->maze->mazePtr[sidx].setCarved(); 
		sy = 0;
		break;
	case 1:
		sy = this->randomInt(2, this->maze->getHeight());
		if (sy % 2 != 0)
			sy = sy - 1;
		sidx = this->maze->getCellIndex(this->maze->getWidth(), sy);
		this->maze->mazePtr[sidx].setEntry();
		this->maze->mazePtr[sidx].setCarved();
		sx = 0;
		break;
	case 2:
		sx = this->randomInt(2, this->maze->getWidth());
		if (sx % 2 != 0)
			sx = sx - 1;
		sidx = this->maze->getCellIndex(sx, this->maze->getHeight());
		this->maze->mazePtr[sidx].setEntry();
		this->maze->mazePtr[sidx].setCarved();
		sy = 0;
		break;
	case 3: // this is the default case
		sy = this->randomInt(2, this->maze->getHeight());
		if (sy % 2 != 0)
			sy = sy - 1;
		sidx = this->maze->getCellIndex(1, sy);
		this->maze->mazePtr[sidx].setEntry();
		this->maze->mazePtr[sidx].setCarved();
		sx = 0;
		break;
	case 4: // this is the case where start is inside maze; leave uncarved so carving algo doesn't mess up
		sx = this->randomInt(2, this->maze->getWidth());
		if (sx % 2 != 0)
			sx = sx - 1;
		sy = this->randomInt(2, this->maze->getHeight());
		if (sy % 2 != 0)
			sy = sy - 1;
		sidx = this->maze->getCellIndex(sx, sy);
		this->maze->mazePtr[sidx].setEntry();
		break;
	default:
		sy = this->randomInt(2, this->maze->getHeight());
		if (sy % 2 != 0)
			sy = sy - 1;
		sidx = this->maze->getCellIndex(1, sy);
		this->maze->mazePtr[sidx].setEntry();
		this->maze->mazePtr[sidx].setCarved();
		sx = 0;
	}
	// pick random exit cell
	switch (this->endEdge) {
	case 0:
		do {
			ex = this->randomInt(2, this->maze->getWidth());
			if (ex % 2 != 0)
				ex = ex - 1;
		} while (sx == ex);
		eidx = this->maze->getCellIndex(ex, 1);
		this->maze->mazePtr[eidx].setExit();
		this->maze->mazePtr[eidx].setCarved();
		break;
	case 1: // this is the default case
		do {
			ey = this->randomInt(2, this->maze->getHeight());
			if (ey % 2 != 0)
				ey = ey - 1;
		} while (sy == ey);
		eidx = this->maze->getCellIndex(this->maze->getWidth(), ey);
		this->maze->mazePtr[eidx].setExit();
		this->maze->mazePtr[eidx].setCarved();
		break;
	case 2:
		do {
			ex = this->randomInt(2, this->maze->getWidth());
			if (ex % 2 != 0)
				ex = ex - 1;
		} while (sx == ex);
		eidx = this->maze->getCellIndex(ex, this->maze->getHeight());
		this->maze->mazePtr[eidx].setExit();
		this->maze->mazePtr[eidx].setCarved();
		break;
	case 3:
		do {
			ey = this->randomInt(2, this->maze->getHeight());
			if (ey % 2 != 0)
				ey = ey - 1;
		} while (ey == sy);
		eidx = this->maze->getCellIndex(1, ey);
		this->maze->mazePtr[eidx].setExit();
		this->maze->mazePtr[eidx].setCarved();
		break;
	case 4: // this is the case where end is inside maze; leave uncarved so carving algo doesn't mess up
		do {
			ex = this->randomInt(2, this->maze->getWidth());
			if (ex % 2 != 0)
				ex = ex - 1;
			ey = this->randomInt(2, this->maze->getHeight());
			if (ey % 2 != 0)
				ey = ey - 1;
		} while (sx == ex && sy == ey);
		eidx = this->maze->getCellIndex(ex, ey);
		this->maze->mazePtr[eidx].setExit();
		break;
	default:
		do {
			ey = this->randomInt(2, this->maze->getHeight());
			if (ey % 2 != 0)
				ey = ey - 1;
		} while (ey == sy);
		eidx = this->maze->getCellIndex(1, ey);
		this->maze->mazePtr[eidx].setExit();
		this->maze->mazePtr[eidx].setCarved();
	}
	return res;
}

RecursiveBacktracker::RecursiveBacktracker(Maze& maze, int startEdge, int endEdge, float bias, bool invertBias, float invertBiasChance, bool prefersLoops)
{
	if (startEdge == endEdge && startEdge != 4) {
		startEdge = 3;
		endEdge = 1;
	}
	if (startEdge < 0 || startEdge > 4)
		startEdge = 3;
	if (endEdge < 0 || endEdge > 4)
		endEdge = 1;
	if (bias < 0 || bias > 1)
		bias = .5;
	if (invertBias)
		invertBias = true;
	if (invertBiasChance <= 0 || invertBiasChance >= 1)
		invertBiasChance = .02f;
	this->maze = &maze;
	this->bias = bias;
	this->startEdge = startEdge;
	this->endEdge = endEdge;
	this->invertBiasChance = invertBiasChance;
	this->prefersLoops = prefersLoops;
	setup();
	generate();
}

RecursiveBacktracker::~RecursiveBacktracker()
{
	this->maze = nullptr;
}

unsigned long long int RecursiveBacktracker::randomInt(unsigned long long int min, unsigned long long int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned long long int> distrib(min, max);
	return distrib(gen);
}

float RecursiveBacktracker::randomFloat() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distrib(0, 1);
	return distrib(gen);
}

bool RecursiveBacktracker::carveNorth(unsigned long long cellX, unsigned long long cellY) {
	this->maze->mazePtr[this->maze->getCellIndex(cellX, (cellY - 1))].setCarved();
	this->maze->mazePtr[this->maze->getCellIndex(cellX, (cellY - 2))].setCarved();
	this->stack.push_back(this->maze->getCellIndex(cellX, (cellY - 2)));
	return true;
}

bool RecursiveBacktracker::carveEast(unsigned long long cellX, unsigned long long cellY) {
	this->maze->mazePtr[this->maze->getCellIndex((cellX + 1), cellY)].setCarved();
	this->maze->mazePtr[this->maze->getCellIndex((cellX + 2), cellY)].setCarved();
	this->stack.push_back(this->maze->getCellIndex((cellX + 2), cellY));
	return true;
}

bool RecursiveBacktracker::carveSouth(unsigned long long cellX, unsigned long long cellY) {
	this->maze->mazePtr[this->maze->getCellIndex(cellX, (cellY + 1))].setCarved();
	this->maze->mazePtr[this->maze->getCellIndex(cellX, (cellY + 2))].setCarved();
	this->stack.push_back(this->maze->getCellIndex(cellX, (cellY + 2)));
	return true;
}

bool RecursiveBacktracker::carveWest(unsigned long long cellX, unsigned long long cellY) {
	this->maze->mazePtr[this->maze->getCellIndex((cellX - 1), cellY)].setCarved();
	this->maze->mazePtr[this->maze->getCellIndex((cellX - 2), cellY)].setCarved();
	this->stack.push_back(this->maze->getCellIndex((cellX - 2), cellY));
	return true;
}

bool RecursiveBacktracker::carveSomeLoops()
{
	if (this->maze->getWidth() < 10 || this->maze->getHeight() < 10)
		return false;
	unsigned long long int limit;
	if (this->maze->getWidth() < this->maze->getHeight()) {
		limit = this->maze->getWidth() / 5;
	}
	else {
		limit = this->maze->getHeight() / 5;
	}
	bool atLeastOneCarved = false;
	while (!atLeastOneCarved || limit > 0) {
		unsigned long long int rx = this->randomInt(2, (this->maze->getWidth() - 1));
		unsigned long long int ry = this->randomInt(2, (this->maze->getHeight() - 1));
		unsigned long long int ri = this->maze->getCellIndex(rx, ry);
		if (this->maze->mazePtr[ri].isHorzNeighbor() || this->maze->mazePtr[ri].isVertNeighbor()) {
			if (!this->maze->mazePtr[ri].isCarved()) {
				atLeastOneCarved = true;
				this->maze->mazePtr[ri].setCarved();
				this->bridges.push_back(ri);
			}
		}
		if (limit > 0)
			limit--;
		else {
			limit = 0;
		}
	}
	return true;
}
