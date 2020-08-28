#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <fstream>

#include "Maze.h"

class Renderer {
	private:
		int marginPixels = 0;
		int cellPixels = 10;
		unsigned char fillR;
		unsigned char fillG;
		unsigned char fillB;
		unsigned char carveR;
		unsigned char carveG;
		unsigned char carveB;
		unsigned char startR;
		unsigned char startG;
		unsigned char startB;
		unsigned char endR;
		unsigned char endG;
		unsigned char endB;
		unsigned char margR;
		unsigned char margG;
		unsigned char margB;
		Maze* maze = nullptr;
		unsigned long long bitmapWidth;
		unsigned long long bitmapHeight;
		unsigned long long numBitmapPixels;
		std::string filename;
		void startRender();
		void writeFileHead(std::fstream &);
		void writeBitmap(std::fstream &);
		bool inMargin(const unsigned long long);
		unsigned long long calcCellX(const unsigned long long);
		unsigned long long calcCellY(const unsigned long long);
		float bitmapXtoCellPerc(const unsigned long long);
		float bitmapYtoCellPerc(const unsigned long long);
	public:
		Renderer(Maze&, std::string = "maze.ppm", int = 0, int = 10, 
				int = 44, int = 82, int = 130, // fill
				int = 180, int = 210, int = 230, // carve
				int = 0, int = 210, int = 0, // start
				int = 210, int = 0, int = 0,  // end
				int = 255, int = 255, int = 255); // margin
		~Renderer();
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