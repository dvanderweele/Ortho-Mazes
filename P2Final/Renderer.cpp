#include "Renderer.h"

#include "Maze.h"
#include <string>
#include <fstream>
#include <iostream>

Renderer::Renderer(Maze& maze, std::string filename, int marginPixels, int cellPixels, int fillR, int fillG, int fillB, int carveR, int carveG, int carveB,
					int startR, int startG, int startB, int endR, int endG, int endB, int margR, int margG, int margB)
{
	this->filename = filename;
	if (marginPixels < 0) {
		this->marginPixels = 0;
	}
	else {
		this->marginPixels = marginPixels;
	}
	if (cellPixels < 1) {
		this->cellPixels = 10;
	}
	else {
		this->cellPixels = cellPixels;
	}
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
	if (fillR < 0 || fillR > 255) {
		this->fillR = 0;
	}
	else {
		this->fillR = fillR;
	}
	if (fillG < 0 || fillG > 255) {
		this->fillG = 0;
	}
	else {
		this->fillG = fillG;
	}
	if (fillB < 0 || fillB > 255) {
		this->fillB = 0;
	}
	else {
		this->fillB = fillB;
	}
	if (carveR < 0 || carveR > 255) {
		this->carveR = 210;
	}
	else {
		this->carveR = carveR;
	}
	if (carveG < 0 || carveG > 255) {
		this->carveG = 230;
	}
	else {
		this->carveG = carveG;
	}
	if (carveB < 0 || carveB > 255) {
		this->carveB = 180;
	}
	else {
		this->carveB = carveB;
	}
	if (startR < 0 || startR > 255) {
		this->startR = 210;
	}
	else {
		this->startR = startR;
	}
	if (startG < 0 || startG > 255) {
		this->startG = 0;
	}
	else {
		this->startG = startG;
	}
	if (startB < 0 || startB > 255) {
		this->startB = 0;
	}
	else {
		this->startB = startB;
	}
	if (endR < 0 || endR > 255) {
		this->endR = 0;
	}
	else {
		this->endR = endR;
	}
	if (endG < 0 || endG > 255) {
		this->endG = 0;
	}
	else {
		this->endG = endG;
	}
	if (endB < 0 || endB > 255) {
		this->endB = 210;
	}
	else {
		this->endB = endB;
	}
	if (margR < 0 || margR > 255) {
		this->margR = 255;
	}
	else {
		this->margR = margR;
	}
	if (margG < 0 || margG > 255) {
		this->margG = 255;
	}
	else {
		this->margG = margG;
	}
	if (margB < 0 || margB > 255) {
		this->margB = 255;
	}
	else {
		this->margB = margB;
	}
	this->maze = &maze;
	this->bitmapWidth = ((unsigned long long)this->maze->getWidth() * this->cellPixels) + (2uLL * this->marginPixels);
	this->bitmapHeight = ((unsigned long long)this->maze->getHeight() * this->cellPixels) + (2uLL * this->marginPixels);
	this->numBitmapPixels = this->bitmapHeight * this->bitmapWidth;
	startRender();
}
Renderer::~Renderer()
{
	this->maze = nullptr;
}
void Renderer::startRender() {
	std::fstream outfile;
	outfile.open(this->filename, std::ios::out);
	if (outfile) {
		writeFileHead(outfile);
		outfile.close();
		outfile.open(this->filename, std::ios::out | std::ios::app | std::ios::binary);
		if (outfile) {
			writeBitmap(outfile);
			outfile.close();
		}
		else {
			std::cout << "Error opening file with name '" << this->filename << " for writing binary image data.'\n";
		}
	}
	else {
		std::cout << "Error creating and/or opening file with name '" << this->filename << ".'\n";
	}
}
void Renderer::writeFileHead(std::fstream &outfile) {
	outfile << "P6 " << this->bitmapWidth << " " << this->bitmapHeight << ' ' << "255" << '\r';
}

void Renderer::writeBitmap(std::fstream &outfile) {
	unsigned long long pixnum = 0;

	/*
		RENDERING FLOW CHART	
		
		if - pixel in margin 
			write margin
		else -
			if - pixel in entry cell
				write start
			else if - pixel in exit cell
				write end
			else - 
				if - pixel in carved cell
					if - horizontal door
					if - vertical door 
					if - one of four weave border types
					else (normally carved corridor)
				else - cell is uncarved
	*/

	while (pixnum < this->numBitmapPixels) {
		if (inMargin(pixnum)) {
			// write margin pixel
			outfile.write(reinterpret_cast<char *>(&this->margR), sizeof(this->margR));
			outfile.write(reinterpret_cast<char *>(&this->margG), sizeof(this->margG));
			outfile.write(reinterpret_cast<char *>(&this->margB), sizeof(this->margB));
		} // end in margin
		else { // start not in margin
			// figure out what maze cell type we're in
			unsigned long long cellIdx = this->maze->getCellIndex(calcCellX(pixnum), calcCellY(pixnum));
			// check if the cell is an entry cell, an exit cell, or another cell type
			if (this->maze->mazePtr[cellIdx].isEntry()) {
				// this is maze start
				outfile.write(reinterpret_cast<char*>(&this->startR), sizeof(this->startR));
				outfile.write(reinterpret_cast<char*>(&this->startG), sizeof(this->startG));
				outfile.write(reinterpret_cast<char*>(&this->startB), sizeof(this->startB));
			} // end is entry
			else if (this->maze->mazePtr[cellIdx].isExit()) {
				// this is maze exit
				outfile.write(reinterpret_cast<char*>(&this->endR), sizeof(this->endR));
				outfile.write(reinterpret_cast<char*>(&this->endG), sizeof(this->endG));
				outfile.write(reinterpret_cast<char*>(&this->endB), sizeof(this->endB));
			} // end is exit
			else { // start carved or uncarved
				// We need to check if maze is carved or uncarved first
				if (this->maze->mazePtr[cellIdx].isCarved()) {
					/*
						cell is carved

						because some carved cell types have some filled and some unfilled pixels,
						we need to check if this pixel needs to be filled or not.
					*/
					float xp = bitmapXtoCellPerc(pixnum);
					float yp = bitmapYtoCellPerc(pixnum);
					if (this->maze->mazePtr[cellIdx].isHorzDoor()) {
						if (yp >= .33 && yp < .6) {
							outfile.write(reinterpret_cast<char*>(&this->fillR), sizeof(this->fillR));
							outfile.write(reinterpret_cast<char*>(&this->fillG), sizeof(this->fillG));
							outfile.write(reinterpret_cast<char*>(&this->fillB), sizeof(this->fillB));
						}
						else {
							outfile.write(reinterpret_cast<char*>(&this->carveR), sizeof(this->carveR));
							outfile.write(reinterpret_cast<char*>(&this->carveG), sizeof(this->carveG));
							outfile.write(reinterpret_cast<char*>(&this->carveB), sizeof(this->carveB));
						}
					}
					else if (this->maze->mazePtr[cellIdx].isVertDoor()) {
						if (xp >= .33 && xp < .6) {
							outfile.write(reinterpret_cast<char*>(&this->fillR), sizeof(this->fillR));
							outfile.write(reinterpret_cast<char*>(&this->fillG), sizeof(this->fillG));
							outfile.write(reinterpret_cast<char*>(&this->fillB), sizeof(this->fillB));
						}
						else {
							outfile.write(reinterpret_cast<char*>(&this->carveR), sizeof(this->carveR));
							outfile.write(reinterpret_cast<char*>(&this->carveG), sizeof(this->carveG));
							outfile.write(reinterpret_cast<char*>(&this->carveB), sizeof(this->carveB));
						}
					}
					else if (this->maze->mazePtr[cellIdx].isNorthWeaveBorder()) {
						if (xp <= .25 || xp >= .75) {
							outfile.write(reinterpret_cast<char*>(&this->fillR), sizeof(this->fillR));
							outfile.write(reinterpret_cast<char*>(&this->fillG), sizeof(this->fillG));
							outfile.write(reinterpret_cast<char*>(&this->fillB), sizeof(this->fillB));
						}
						else {
							if (yp >= .75) {
								outfile.write(reinterpret_cast<char*>(&this->fillR), sizeof(this->fillR));
								outfile.write(reinterpret_cast<char*>(&this->fillG), sizeof(this->fillG));
								outfile.write(reinterpret_cast<char*>(&this->fillB), sizeof(this->fillB));
							} else {
								outfile.write(reinterpret_cast<char*>(&this->carveR), sizeof(this->carveR));
								outfile.write(reinterpret_cast<char*>(&this->carveG), sizeof(this->carveG));
								outfile.write(reinterpret_cast<char*>(&this->carveB), sizeof(this->carveB));
							}
						}
					}
					else if (this->maze->mazePtr[cellIdx].isEastWeaveBorder()) {
						if (yp <= .25 || yp >= .75) {
							outfile.write(reinterpret_cast<char*>(&this->fillR), sizeof(this->fillR));
							outfile.write(reinterpret_cast<char*>(&this->fillG), sizeof(this->fillG));
							outfile.write(reinterpret_cast<char*>(&this->fillB), sizeof(this->fillB));
						}
						else {
							if (xp <= .25) {
								outfile.write(reinterpret_cast<char*>(&this->fillR), sizeof(this->fillR));
								outfile.write(reinterpret_cast<char*>(&this->fillG), sizeof(this->fillG));
								outfile.write(reinterpret_cast<char*>(&this->fillB), sizeof(this->fillB));
							}
							else {
								outfile.write(reinterpret_cast<char*>(&this->carveR), sizeof(this->carveR));
								outfile.write(reinterpret_cast<char*>(&this->carveG), sizeof(this->carveG));
								outfile.write(reinterpret_cast<char*>(&this->carveB), sizeof(this->carveB));
							}
						}
					}
					else if (this->maze->mazePtr[cellIdx].isSouthWeaveBorder()) {
						if (xp <= .25 || xp >= .75) {
							outfile.write(reinterpret_cast<char*>(&this->fillR), sizeof(this->fillR));
							outfile.write(reinterpret_cast<char*>(&this->fillG), sizeof(this->fillG));
							outfile.write(reinterpret_cast<char*>(&this->fillB), sizeof(this->fillB));
						}
						else {
							if (yp <= .25) {
								outfile.write(reinterpret_cast<char*>(&this->fillR), sizeof(this->fillR));
								outfile.write(reinterpret_cast<char*>(&this->fillG), sizeof(this->fillG));
								outfile.write(reinterpret_cast<char*>(&this->fillB), sizeof(this->fillB));
							}
							else {
								outfile.write(reinterpret_cast<char*>(&this->carveR), sizeof(this->carveR));
								outfile.write(reinterpret_cast<char*>(&this->carveG), sizeof(this->carveG));
								outfile.write(reinterpret_cast<char*>(&this->carveB), sizeof(this->carveB));
							}
						}
					}
					else if (this->maze->mazePtr[cellIdx].isWestWeaveBorder()) {
						if (yp <= .25 || yp >= .75) {
							outfile.write(reinterpret_cast<char*>(&this->fillR), sizeof(this->fillR));
							outfile.write(reinterpret_cast<char*>(&this->fillG), sizeof(this->fillG));
							outfile.write(reinterpret_cast<char*>(&this->fillB), sizeof(this->fillB));
						}
						else {
							if (xp >= .75) {
								outfile.write(reinterpret_cast<char*>(&this->fillR), sizeof(this->fillR));
								outfile.write(reinterpret_cast<char*>(&this->fillG), sizeof(this->fillG));
								outfile.write(reinterpret_cast<char*>(&this->fillB), sizeof(this->fillB));
							}
							else {
								outfile.write(reinterpret_cast<char*>(&this->carveR), sizeof(this->carveR));
								outfile.write(reinterpret_cast<char*>(&this->carveG), sizeof(this->carveG));
								outfile.write(reinterpret_cast<char*>(&this->carveB), sizeof(this->carveB));
							}
						}
					}
					else {
						outfile.write(reinterpret_cast<char*>(&this->carveR), sizeof(this->carveR));
						outfile.write(reinterpret_cast<char*>(&this->carveG), sizeof(this->carveG));
						outfile.write(reinterpret_cast<char*>(&this->carveB), sizeof(this->carveB));
					}
				}
				else {
					// cell is uncarved
					outfile.write(reinterpret_cast<char*>(&this->fillR), sizeof(this->fillR));
					outfile.write(reinterpret_cast<char*>(&this->fillG), sizeof(this->fillG));
					outfile.write(reinterpret_cast<char*>(&this->fillB), sizeof(this->fillB));
				}
			} // end carved or uncarved
		} // end not in margin
		pixnum++;
	} // end while
} // end writebitmap

bool Renderer::inMargin(const unsigned long long bitmapIndex) {
	bool res;
	unsigned long long bitmapX = bitmapIndex % this->bitmapWidth;
	unsigned long long bitmapY = (bitmapIndex / this->bitmapWidth) + 1;
	if ((bitmapX < this->marginPixels) || (bitmapX >= (this->bitmapWidth - this->marginPixels))
		|| (bitmapY < this->marginPixels) || (bitmapY >= (this->bitmapHeight - this->marginPixels))) {
		res = true;
	}
	else {
		res = false;
	}
	return res;
}

unsigned long long Renderer::calcCellX(const unsigned long long bitmapIndex) {
	unsigned long long cellX = 1;
	unsigned long long bitmapX = bitmapIndex % this->bitmapWidth;
	cellX = ((bitmapX - this->marginPixels) / this->cellPixels) + 1;
	return cellX;
}

unsigned long long Renderer::calcCellY(const unsigned long long bitmapIndex) {
	unsigned long long cellY = 1;
	unsigned long long bitmapY = (bitmapIndex / this->bitmapWidth) + 1;
	cellY = ((bitmapY - this->marginPixels) / this->cellPixels) + 1;
	return cellY;
}

float Renderer::bitmapXtoCellPerc(const unsigned long long bitmapIndex) {
	float percentage = 0.0f;
	unsigned long long bitmapX = bitmapIndex % this->bitmapWidth;
	unsigned long long cellX = calcCellX(bitmapIndex);
	unsigned long long cellStart = this->marginPixels + ((cellX - 1) * this->cellPixels);
	unsigned long int vec = bitmapX - cellStart;
	percentage = (float)vec / this->cellPixels;
	return percentage;
}

float Renderer::bitmapYtoCellPerc(const unsigned long long bitmapIndex) {
	float percentage = 0.0;
	unsigned long long bitmapY = (bitmapIndex / this->bitmapWidth) + 1;
	unsigned long long cellY = calcCellY(bitmapIndex);
	unsigned long long cellStart = this->marginPixels + ((cellY - 1) * this->cellPixels);
	unsigned long int vec = bitmapY - cellStart;
	percentage = (float)vec / this->cellPixels;
	return percentage;
}