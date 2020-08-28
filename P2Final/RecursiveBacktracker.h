#ifndef RECURSIVE_BACKTRACKER_H
#define RECURSIVE_BACKTRACKER_H

#include <vector>

#include "Maze.h"

class RecursiveBacktracker {
	private: 
		Maze* maze = nullptr;
		int startEdge = 3;
		int endEdge = 1;
		std::vector<unsigned long long int> stack;
		float bias = .5;
		bool generate();
		bool setup();
		bool invertBias = false;
		float invertBiasChance = .02f;
		bool prefersLoops = false;
		unsigned long long int randomInt(unsigned long long int, unsigned long long int);
		float randomFloat();
		bool carveNorth(unsigned long long, unsigned long long);
		bool carveEast(unsigned long long, unsigned long long);
		bool carveSouth(unsigned long long, unsigned long long);
		bool carveWest(unsigned long long, unsigned long long);
		bool carveSomeLoops();
	public: 
		RecursiveBacktracker(Maze&, int = 3, int = 1, float = .5, bool = false, float = .02f, bool = false);
		~RecursiveBacktracker();
		std::vector<unsigned long long> bridges;
};

#endif