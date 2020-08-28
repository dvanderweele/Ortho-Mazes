#ifndef RB_RENDERER_H
#define RB_RENDERER_H

#include <string>
#include <fstream>
#include <vector>

#include "Maze.h"

class RbRenderer {
private:
	int mode;
	int anchor;
	int marginPixels = 0;
	int cellPixels = 10;
	unsigned char fillR;
	unsigned char fillG;
	unsigned char fillB;
	unsigned char carveR;
	unsigned char carveG;
	unsigned char carveB;
	unsigned char margR;
	unsigned char margG;
	unsigned char margB;
	bool rinc;
	bool ginc;
	bool binc;
	Maze* maze = nullptr;
	unsigned long long bitmapWidth;
	unsigned long long bitmapHeight;
	unsigned long long numBitmapPixels;

	struct Area {
		unsigned long long int areaCode;
		unsigned char red;
		unsigned char green;
		unsigned char blue;
	};
	std::vector<Area> areas;
	unsigned long long int extractAreaCode(unsigned long long);

	unsigned char calcDynamicRed(unsigned long long);
	unsigned char calcDynamicGreen(unsigned long long);
	unsigned char calcDynamicBlue(unsigned long long);

	std::string filename;
	void writeFileHead(std::fstream&);
	void writeBitmap(std::fstream&);
	bool inMargin(const unsigned long long);
	unsigned long long calcCellX(const unsigned long long);
	unsigned long long calcCellY(const unsigned long long);
	float bitmapXtoCellPerc(const unsigned long long);
	float bitmapYtoCellPerc(const unsigned long long);
	unsigned long long int randomInt(unsigned long long int, unsigned long long int);
public:
	RbRenderer(Maze&, std::string = "maze.ppm", int = 0, int = 10,
		int = 2, int = 255, int = 255, int = 255, int = 0); 
	~RbRenderer();
	void buildAreaCodes(std::vector<unsigned long long int>&);
	void startRender();
	/*
		RENDERER DEFAULTS LEGEND

		filename = maze.ppm
		marginPixels = 0
		cellPixels = 10
					RRR  GGG  BBB
		fillRGB   =	 44,  82, 130 = dark blue
		carveRGB  = 180, 210, 230 = light blue
		startRGB  =   0, 210,   0 = green
		endRGB    = 210,   0,   0 = salmon
		marginRGB = 255, 255, 255 = white
	*/
};

#endif
