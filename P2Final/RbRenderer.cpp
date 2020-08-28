#include "RbRenderer.h"

#include "RbRecursiveBacktracker.h"
#include <random>
#include <string>
#include <fstream>
#include <iostream>

/*
	Rainbow Renderer Modes and Anchor Points Legend

	Note: no matter these options, the color rendering of carved pixels/cells will work the same, 
	based on the areaCodes. However, these options do affect how filled pixels/cells are colored
	and rendered. Essentially, in static mode, all the filled pixels/cells will be the same color,
	either a randomly generated light color or dark color (with light vs dark here affecting whether 
	the auto-generated color sequence for carved cells w/ area codes are in the dark or light range).
	In dynamic mode, a gradient will be generated for the filled cells, existing either in the dark 
	or light color range and stretching from the anchoring point chosen.

	MODES
	1 - static, randomly generate light fill color
	2 - static, randomly generate dark fill color
	3 - dynamic, light range for fill color
	4 - dynamic, dark range for fill color

	ANCHOR POINTS
	0 - top left corner
	1 - top edge
	2 - top right corner
	3 - right edge
	4 - bottom right corner
	5 - bottom edge
	6 - bottom left corner
	7 - left edge
	8 - center
*/

RbRenderer::RbRenderer(Maze& maze, std::string filename, int marginPixels, int cellPixels,
	int mode, int margR, int margG, int margB, int anchor)
{
	this->filename = filename;
	if (mode < 1 || mode > 4)
		mode = 2;
	if (anchor < 0 || anchor > 8)
		anchor = 0;
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

	this->mode = mode;
	this->anchor = anchor;

	this->bitmapWidth = ((unsigned long long)this->maze->getWidth() * this->cellPixels) + (2uLL * this->marginPixels);
	this->bitmapHeight = ((unsigned long long)this->maze->getHeight() * this->cellPixels) + (2uLL * this->marginPixels);
	this->numBitmapPixels = this->bitmapHeight * this->bitmapWidth;
}
RbRenderer::~RbRenderer()
{
	this->maze = nullptr;
}
void RbRenderer::buildAreaCodes(std::vector<unsigned long long int>& areaCodes)
{
	switch (this->mode) {
	case 1:
		this->fillR = this->randomInt(180, 255);
		this->fillG = this->randomInt(180, 255);
		this->fillB = this->randomInt(180, 255);
		this->carveR = this->randomInt(0, 75);
		if (this->carveR < 32)
			this->rinc = true;
		else
			this->rinc = false;
		this->carveB = this->randomInt(0, 75);
		if (this->carveB < 32)
			this->binc = true;
		else
			this->binc = false;
		this->carveG = this->randomInt(0, 75);
		if (this->carveG < 32)
			this->ginc = true;
		else
			this->ginc = false;
		for (unsigned long long areaCode : areaCodes) {
			if (this->carveR + 10 > 75) {
				this->rinc = false;
				this->carveR -= 10;
			}
			else if (this->carveR - 10 < 0) {
				this->rinc = true;
				this->carveR += 10;
			}
			else {
				if (rinc)
					this->carveR += 10;
				else
					this->carveR -= 10;
			}
			if (this->carveG + 10 > 75) {
				this->ginc = false;
				this->carveG -= 10;
			}
			else if (this->carveG - 10 < 0) {
				this->ginc = true;
				this->carveG += 10;
			}
			else {
				if (ginc)
					this->carveG += 10;
				else
					this->carveG -= 10;
			}
			if (this->carveB + 10 > 75) {
				this->binc = false;
				this->carveB -= 10;
			}
			else if (this->carveB - 10 < 0) {
				this->binc = true;
				this->carveB += 10;
			}
			else {
				if (binc)
					this->carveB += 10;
				else
					this->carveB -= 10;
			}
			Area area = { areaCode, this->carveR, this->carveG, this->carveB };
			this->areas.push_back(area);
		}
		break;
	case 2:
		this->fillR = this->randomInt(0, 75);
		this->fillG = this->randomInt(0, 75);
		this->fillB = this->randomInt(0, 75);
		this->carveR = this->randomInt(180, 255);
		if (this->carveR < 112)
			this->rinc = true;
		else
			this->rinc = false;
		this->carveB = this->randomInt(180, 255);
		if (this->carveB < 112)
			this->binc = true;
		else
			this->binc = false;
		this->carveG = this->randomInt(180, 255);
		if (this->carveG < 112)
			this->ginc = true;
		else
			this->ginc = false;
		for (unsigned long long areaCode : areaCodes) {
			if (this->carveR + 10 > 255) {
				this->rinc = false;
				this->carveR -= 10;
			}
			else if (this->carveR - 10 < 180) {
				this->rinc = true;
				this->carveR += 10;
			}
			else {
				if (rinc)
					this->carveR += 10;
				else
					this->carveR -= 10;
			}
			if (this->carveG + 10 > 255) {
				this->ginc = false;
				this->carveG -= 10;
			}
			else if (this->carveG - 10 < 180) {
				this->ginc = true;
				this->carveG += 10;
			}
			else {
				if (ginc)
					this->carveG += 10;
				else
					this->carveG -= 10;
			}
			if (this->carveB + 10 > 255) {
				this->binc = false;
				this->carveB -= 10;
			}
			else if (this->carveB - 10 < 180) {
				this->binc = true;
				this->carveB += 10;
			}
			else {
				if (binc)
					this->carveB += 10;
				else
					this->carveB -= 10;
			}
			Area area = { areaCode, this->carveR, this->carveG, this->carveB };
			this->areas.push_back(area);
		}
		break;
	case 3:
		this->fillR = this->randomInt(180, 255);
		this->fillG = this->randomInt(180, 255);
		this->fillB = this->randomInt(180, 255);
		this->carveR = this->randomInt(0, 75);
		if (this->carveR < 32)
			this->rinc = true;
		else
			this->rinc = false;
		this->carveB = this->randomInt(0, 75);
		if (this->carveB < 32)
			this->binc = true;
		else
			this->binc = false;
		this->carveG = this->randomInt(0, 75);
		if (this->carveG < 32)
			this->ginc = true;
		else
			this->ginc = false;
		for (unsigned long long areaCode : areaCodes) {
			if (this->carveR + 10 > 75) {
				this->rinc = false;
				this->carveR -= 10;
			}
			else if (this->carveR - 10 < 0) {
				this->rinc = true;
				this->carveR += 10;
			}
			else {
				if (rinc)
					this->carveR += 10;
				else
					this->carveR -= 10;
			}
			if (this->carveG + 10 > 75) {
				this->ginc = false;
				this->carveG -= 10;
			}
			else if (this->carveG - 10 < 0) {
				this->ginc = true;
				this->carveG += 10;
			}
			else {
				if (ginc)
					this->carveG += 10;
				else
					this->carveG -= 10;
			}
			if (this->carveB + 10 > 75) {
				this->binc = false;
				this->carveB -= 10;
			}
			else if (this->carveB - 10 < 0) {
				this->binc = true;
				this->carveB += 10;
			}
			else {
				if (binc)
					this->carveB += 10;
				else
					this->carveB -= 10;
			}
			Area area = { areaCode, this->carveR, this->carveG, this->carveB };
			this->areas.push_back(area);
		}
		break;
	case 4:
		this->fillR = this->randomInt(0, 75);
		this->fillG = this->randomInt(0, 75);
		this->fillB = this->randomInt(0, 75);
		this->carveR = this->randomInt(180, 255);
		if (this->carveR < 112)
			this->rinc = true;
		else
			this->rinc = false;
		this->carveB = this->randomInt(180, 255);
		if (this->carveB < 112)
			this->binc = true;
		else
			this->binc = false;
		this->carveG = this->randomInt(180, 255);
		if (this->carveG < 112)
			this->ginc = true;
		else
			this->ginc = false;
		for (unsigned long long areaCode : areaCodes) {
			if (this->carveR + 5 > 255) {
				this->rinc = false;
				this->carveR -= 5;
			}
			else if (this->carveR - 5 < 180) {
				this->rinc = true;
				this->carveR += 5;
			}
			else {
				if (rinc)
					this->carveR += 5;
				else
					this->carveR -= 5;
			}
			if (this->carveG + 5 > 255) {
				this->ginc = false;
				this->carveG -= 5;
			}
			else if (this->carveG - 5 < 180) {
				this->ginc = true;
				this->carveG += 5;
			}
			else {
				if (ginc)
					this->carveG += 5;
				else
					this->carveG -= 5;
			}
			if (this->carveB + 5 > 255) {
				this->binc = false;
				this->carveB -= 5;
			}
			else if (this->carveB - 5 < 180) {
				this->binc = true;
				this->carveB += 5;
			}
			else {
				if (binc)
					this->carveB += 5;
				else
					this->carveB -= 5;
			}
			Area area = { areaCode, this->carveR, this->carveG, this->carveB };
			this->areas.push_back(area);
		}
		break;
	}
}
void RbRenderer::startRender() {
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
void RbRenderer::writeFileHead(std::fstream& outfile) {
	outfile << "P6 " << this->bitmapWidth << " " << this->bitmapHeight << ' ' << "255" << '\r';
}

void RbRenderer::writeBitmap(std::fstream& outfile) {
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
			outfile.write(reinterpret_cast<char*>(&this->margR), sizeof(this->margR));
			outfile.write(reinterpret_cast<char*>(&this->margG), sizeof(this->margG));
			outfile.write(reinterpret_cast<char*>(&this->margB), sizeof(this->margB));
		} // end in margin
		else { // start not in margin
			// figure out what maze cell type we're in
			unsigned long long cellIdx = this->maze->getCellIndex(calcCellX(pixnum), calcCellY(pixnum));
			unsigned long long vi = this->extractAreaCode(cellIdx);
			unsigned long long vo;
			if (vi == 0) {
				vo = 0;
			}
			else {
				vo = vi - 1;
			}
			unsigned char red = this->areas[vo].red;
			unsigned char green = this->areas[vo].green;
			unsigned char blue = this->areas[vo].blue;
			unsigned char fred;
			unsigned char fgreen;
			unsigned char fblue;
			if (this->mode == 1 || this->mode == 2) {
				fred = this->fillR;
				fgreen = this->fillG;
				fblue = this->fillB;
			}
			else {
				fred = this->calcDynamicRed(pixnum);
				fgreen = this->calcDynamicGreen(pixnum);
				fblue = this->calcDynamicBlue(pixnum);
			}
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
						outfile.write(reinterpret_cast<char*>(&fred), sizeof(fred));
						outfile.write(reinterpret_cast<char*>(&fgreen), sizeof(fgreen));
						outfile.write(reinterpret_cast<char*>(&fblue), sizeof(fblue));
					}
					else {
						outfile.write(reinterpret_cast<char*>(&red), sizeof(red));
						outfile.write(reinterpret_cast<char*>(&green), sizeof(green));
						outfile.write(reinterpret_cast<char*>(&blue), sizeof(blue));
					}
				}
				else if (this->maze->mazePtr[cellIdx].isVertDoor()) {
					if (xp >= .33 && xp < .6) {
						outfile.write(reinterpret_cast<char*>(&fred), sizeof(fred));
						outfile.write(reinterpret_cast<char*>(&fgreen), sizeof(fgreen));
						outfile.write(reinterpret_cast<char*>(&fblue), sizeof(fblue));
					}
					else {
						outfile.write(reinterpret_cast<char*>(&red), sizeof(red));
						outfile.write(reinterpret_cast<char*>(&green), sizeof(green));
						outfile.write(reinterpret_cast<char*>(&blue), sizeof(blue));
					}
				}
				else if (this->maze->mazePtr[cellIdx].isNorthWeaveBorder()) {
					if (xp <= .25 || xp >= .75) {
						outfile.write(reinterpret_cast<char*>(&fred), sizeof(fred));
						outfile.write(reinterpret_cast<char*>(&fgreen), sizeof(fgreen));
						outfile.write(reinterpret_cast<char*>(&fblue), sizeof(fblue));
					}
					else {
						if (yp >= .75) {
							outfile.write(reinterpret_cast<char*>(&fred), sizeof(fred));
							outfile.write(reinterpret_cast<char*>(&fgreen), sizeof(fgreen));
							outfile.write(reinterpret_cast<char*>(&fblue), sizeof(fblue));
						}
						else {
							outfile.write(reinterpret_cast<char*>(&red), sizeof(red));
							outfile.write(reinterpret_cast<char*>(&green), sizeof(green));
							outfile.write(reinterpret_cast<char*>(&blue), sizeof(blue));
						}
					}
				}
				else if (this->maze->mazePtr[cellIdx].isEastWeaveBorder()) {
					if (yp <= .25 || yp >= .75) {
						outfile.write(reinterpret_cast<char*>(&fred), sizeof(fred));
						outfile.write(reinterpret_cast<char*>(&fgreen), sizeof(fgreen));
						outfile.write(reinterpret_cast<char*>(&fblue), sizeof(fblue));
					}
					else {
						if (xp <= .25) {
							outfile.write(reinterpret_cast<char*>(&fred), sizeof(fred));
							outfile.write(reinterpret_cast<char*>(&fgreen), sizeof(fgreen));
							outfile.write(reinterpret_cast<char*>(&fblue), sizeof(fblue));
						}
						else {
							outfile.write(reinterpret_cast<char*>(&red), sizeof(red));
							outfile.write(reinterpret_cast<char*>(&green), sizeof(green));
							outfile.write(reinterpret_cast<char*>(&blue), sizeof(blue));
						}
					}
				}
				else if (this->maze->mazePtr[cellIdx].isSouthWeaveBorder()) {
					if (xp <= .25 || xp >= .75) {
						outfile.write(reinterpret_cast<char*>(&fred), sizeof(fred));
						outfile.write(reinterpret_cast<char*>(&fgreen), sizeof(fgreen));
						outfile.write(reinterpret_cast<char*>(&fblue), sizeof(fblue));
					}
					else {
						if (yp <= .25) {
							outfile.write(reinterpret_cast<char*>(&fred), sizeof(fred));
							outfile.write(reinterpret_cast<char*>(&fgreen), sizeof(fgreen));
							outfile.write(reinterpret_cast<char*>(&fblue), sizeof(fblue));
						}
						else {
							outfile.write(reinterpret_cast<char*>(&red), sizeof(red));
							outfile.write(reinterpret_cast<char*>(&green), sizeof(green));
							outfile.write(reinterpret_cast<char*>(&blue), sizeof(blue));
						}
					}
				}
				else if (this->maze->mazePtr[cellIdx].isWestWeaveBorder()) {
					if (yp <= .25 || yp >= .75) {
						outfile.write(reinterpret_cast<char*>(&fred), sizeof(fred));
						outfile.write(reinterpret_cast<char*>(&fgreen), sizeof(fgreen));
						outfile.write(reinterpret_cast<char*>(&fblue), sizeof(fblue));
					}
					else {
						if (xp >= .75) {
							outfile.write(reinterpret_cast<char*>(&fred), sizeof(fred));
							outfile.write(reinterpret_cast<char*>(&fgreen), sizeof(fgreen));
							outfile.write(reinterpret_cast<char*>(&fblue), sizeof(fblue));
						}
						else {
							outfile.write(reinterpret_cast<char*>(&red), sizeof(red));
							outfile.write(reinterpret_cast<char*>(&green), sizeof(green));
							outfile.write(reinterpret_cast<char*>(&blue), sizeof(blue));
						}
					}
				}
				else {
					outfile.write(reinterpret_cast<char*>(&red), sizeof(red));
					outfile.write(reinterpret_cast<char*>(&green), sizeof(green));
					outfile.write(reinterpret_cast<char*>(&blue), sizeof(blue));
				}
			}
			else {
				// cell is uncarved
				outfile.write(reinterpret_cast<char*>(&fred), sizeof(fred));
				outfile.write(reinterpret_cast<char*>(&fgreen), sizeof(fgreen));
				outfile.write(reinterpret_cast<char*>(&fblue), sizeof(fblue));
			} // end carved or uncarved
		} // end not in margin
		pixnum++;
	} // end while
} // end writebitmap

bool RbRenderer::inMargin(const unsigned long long bitmapIndex) {
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

unsigned long long RbRenderer::calcCellX(const unsigned long long bitmapIndex) {
	unsigned long long cellX = 1;
	unsigned long long bitmapX = bitmapIndex % this->bitmapWidth;
	cellX = ((bitmapX - this->marginPixels) / this->cellPixels) + 1;
	return cellX;
}

unsigned long long RbRenderer::calcCellY(const unsigned long long bitmapIndex) {
	unsigned long long cellY = 1;
	unsigned long long bitmapY = (bitmapIndex / this->bitmapWidth) + 1;
	cellY = ((bitmapY - this->marginPixels) / this->cellPixels) + 1;
	return cellY;
}

float RbRenderer::bitmapXtoCellPerc(const unsigned long long bitmapIndex) {
	float percentage = 0.0f;
	unsigned long long bitmapX = bitmapIndex % this->bitmapWidth;
	unsigned long long cellX = calcCellX(bitmapIndex);
	unsigned long long cellStart = this->marginPixels + ((cellX - 1) * this->cellPixels);
	unsigned long int vec = bitmapX - cellStart;
	percentage = (float)vec / this->cellPixels;
	return percentage;
}

float RbRenderer::bitmapYtoCellPerc(const unsigned long long bitmapIndex) {
	float percentage = 0.0;
	unsigned long long bitmapY = (bitmapIndex / this->bitmapWidth) + 1;
	unsigned long long cellY = calcCellY(bitmapIndex);
	unsigned long long cellStart = this->marginPixels + ((cellY - 1) * this->cellPixels);
	unsigned long int vec = bitmapY - cellStart;
	percentage = (float)vec / this->cellPixels;
	return percentage;
}

unsigned long long int RbRenderer::randomInt(unsigned long long int min, unsigned long long int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<unsigned long long int> distrib(min, max);
	return distrib(gen);
}


unsigned long long int RbRenderer::extractAreaCode(unsigned long long cellIdx) {
	unsigned long long val = this->maze->mazePtr[cellIdx].getRaw() >> 20;
	return val;
}

/*
	ANCHOR POINTS
	0 - top left corner
	1 - top edge
	2 - top right corner
	3 - right edge
	4 - bottom right corner
	5 - bottom edge
	6 - bottom left corner
	7 - left edge
	8 - center
*/

unsigned char RbRenderer::calcDynamicRed(unsigned long long pixnum) {
	unsigned long long bitmapX = pixnum % this->bitmapWidth;
	unsigned long long bitmapY = (pixnum / this->bitmapWidth) + 1;
	unsigned long long qd, ax, ay;
	float extent = 0.0f;
	float p = 0.0f;
	qd = 0;
	switch (this->anchor) {
	case 0: // top left corner is anchor
		qd = sqrt((bitmapX * bitmapX) + (bitmapY * bitmapY));
		extent = sqrt((this->bitmapWidth * this->bitmapWidth) + (this->bitmapHeight * this->bitmapHeight));
		p = qd / extent;
		break;
	case 1: // top edge is anchor
		qd = bitmapY;
		extent = this->bitmapHeight;
		p = bitmapY / extent;
		break;
	case 2: // top right corner is anchor
		qd = sqrt(((this->bitmapWidth - bitmapX)*(this->bitmapWidth - bitmapX)) + (bitmapY * bitmapY));
		extent = sqrt((this->bitmapWidth * this->bitmapWidth) + (this->bitmapHeight * this->bitmapHeight));
		p = qd / extent;
		break;
	case 3: // right edge is anchor
		qd = this->bitmapWidth - bitmapX;
		extent = this->bitmapWidth;
		p = qd / extent;
		break;
	case 4: // bottom right corner is anchor
		qd = sqrt(((this->bitmapWidth - bitmapX) * (this->bitmapWidth - bitmapX)) + ((this->bitmapHeight - bitmapY) * (this->bitmapHeight - bitmapY)));
		extent = sqrt((this->bitmapWidth * this->bitmapWidth) + (this->bitmapHeight * this->bitmapHeight));
		p = qd / extent;
		break;
	case 5: // bottom edge is anchor
		qd = this->bitmapHeight - bitmapY;
		extent = this->bitmapHeight;
		p = qd / extent;
		break;
	case 6: // bottom left corner is anchor
		qd = sqrt((bitmapX * bitmapX) + ((this->bitmapHeight - bitmapY) * (this->bitmapHeight - bitmapY)));
		extent = sqrt((this->bitmapWidth * this->bitmapWidth) + (this->bitmapHeight * this->bitmapHeight));
		p = qd / extent;
		break;
	case 7: // left edge is anchor
		qd = bitmapX;
		extent = this->bitmapWidth;
		p = qd / extent;
		break;
	case 8: // center is anchor
		ax = this->bitmapWidth / 2;
		ay = this->bitmapHeight / 2;
		extent = sqrt((ax * ax) + (ay * ay));
		if (bitmapX > ax) {
			if (bitmapY > ay) {
				qd = sqrt(((bitmapX - ax)*(bitmapX-ax)) + ((bitmapY-ay)*(bitmapY-ay)));
			}
			else {
				qd = sqrt(((bitmapX - ax) * (bitmapX - ax)) + ((ay - bitmapY) * (ay - bitmapY)));
			}
		}
		else {
			if (bitmapY > ay) {
				qd = sqrt(((ax - bitmapX) * (ax - bitmapX)) + ((bitmapY - ay) * (bitmapY - ay)));
			}
			else {
				qd = sqrt(((ax - bitmapX) * (ax - bitmapX)) + ((ay - bitmapY) * (ay - bitmapY)));
			}
		}
		p = qd / extent;
		break;
	}
	if (qd == 0) {
		return this->fillR;
	}
	else {
		int gp = (int)(p * 35);
		unsigned char res;
		if (this->mode == 3) {
			// light gradient mode
			if ((int)this->fillR > 215) {
				res = (unsigned char)((int)this->fillR - gp);
			}
			else {
				res = (unsigned char)((int)this->fillR + gp);
			}
		}
		else {
			// dark gradient mode
			if ((int)this->fillR > 35) {
				res = (unsigned char)((int)this->fillR - gp);
			}
			else {
				res = (unsigned char)((int)this->fillR + gp);
			}
		}
		return res;
	}
}
unsigned char RbRenderer::calcDynamicGreen(unsigned long long pixnum) {
	unsigned long long bitmapX = pixnum % this->bitmapWidth;
	unsigned long long bitmapY = (pixnum / this->bitmapWidth) + 1;
	unsigned long long qd, ax, ay;
	float extent = 0.0f;
	float p = 0.0f;
	qd = 0;
	switch (this->anchor) {
	case 0: // top left corner is anchor
		qd = sqrt((bitmapX * bitmapX) + (bitmapY * bitmapY));
		extent = sqrt((this->bitmapWidth * this->bitmapWidth) + (this->bitmapHeight * this->bitmapHeight));
		p = qd / extent;
		break;
	case 1: // top edge is anchor
		qd = bitmapY;
		extent = this->bitmapHeight;
		p = bitmapY / extent;
		break;
	case 2: // top right corner is anchor
		qd = sqrt(((this->bitmapWidth - bitmapX) * (this->bitmapWidth - bitmapX)) + (bitmapY * bitmapY));
		extent = sqrt((this->bitmapWidth * this->bitmapWidth) + (this->bitmapHeight * this->bitmapHeight));
		p = qd / extent;
		break;
	case 3: // right edge is anchor
		qd = this->bitmapWidth - bitmapX;
		extent = this->bitmapWidth;
		p = qd / extent;
		break;
	case 4: // bottom right corner is anchor
		qd = sqrt(((this->bitmapWidth - bitmapX) * (this->bitmapWidth - bitmapX)) + ((this->bitmapHeight - bitmapY) * (this->bitmapHeight - bitmapY)));
		extent = sqrt((this->bitmapWidth * this->bitmapWidth) + (this->bitmapHeight * this->bitmapHeight));
		p = qd / extent;
		break;
	case 5: // bottom edge is anchor
		qd = this->bitmapHeight - bitmapY;
		extent = this->bitmapHeight;
		p = qd / extent;
		break;
	case 6: // bottom left corner is anchor
		qd = sqrt((bitmapX * bitmapX) + ((this->bitmapHeight - bitmapY) * (this->bitmapHeight - bitmapY)));
		extent = sqrt((this->bitmapWidth * this->bitmapWidth) + (this->bitmapHeight * this->bitmapHeight));
		p = qd / extent;
		break;
	case 7: // left edge is anchor
		qd = bitmapX;
		extent = this->bitmapWidth;
		p = qd / extent;
		break;
	case 8: // center is anchor
		ax = this->bitmapWidth / 2;
		ay = this->bitmapHeight / 2;
		extent = sqrt((ax * ax) + (ay * ay));
		if (bitmapX > ax) {
			if (bitmapY > ay) {
				qd = sqrt(((bitmapX - ax) * (bitmapX - ax)) + ((bitmapY - ay) * (bitmapY - ay)));
			}
			else {
				qd = sqrt(((bitmapX - ax) * (bitmapX - ax)) + ((ay - bitmapY) * (ay - bitmapY)));
			}
		}
		else {
			if (bitmapY > ay) {
				qd = sqrt(((ax - bitmapX) * (ax - bitmapX)) + ((bitmapY - ay) * (bitmapY - ay)));
			}
			else {
				qd = sqrt(((ax - bitmapX) * (ax - bitmapX)) + ((ay - bitmapY) * (ay - bitmapY)));
			}
		}
		p = qd / extent;
		break;
	}
	if (qd == 0) {
		return this->fillG;
	}
	else {
		int gp = (int)(p * 35);
		unsigned char res;
		if (this->mode == 3) {
			// light gradient mode
			if ((int)this->fillG > 215) {
				res = (unsigned char)((int)this->fillG - gp);
			}
			else {
				res = (unsigned char)((int)this->fillG + gp);
			}
		}
		else {
			// dark gradient mode
			if ((int)this->fillG > 35) {
				res = (unsigned char)((int)this->fillG - gp);
			}
			else {
				res = (unsigned char)((int)this->fillG + gp);
			}
		}
		return res;
	}
}
unsigned char RbRenderer::calcDynamicBlue(unsigned long long pixnum) {
	unsigned long long bitmapX = pixnum % this->bitmapWidth;
	unsigned long long bitmapY = (pixnum / this->bitmapWidth) + 1;
	unsigned long long qd, ax, ay;
	float extent = 0.0f;
	float p = 0.0f;
	qd = 0;
	switch (this->anchor) {
	case 0: // top left corner is anchor
		qd = sqrt((bitmapX * bitmapX) + (bitmapY * bitmapY));
		extent = sqrt((this->bitmapWidth * this->bitmapWidth) + (this->bitmapHeight * this->bitmapHeight));
		p = qd / extent;
		break;
	case 1: // top edge is anchor
		qd = bitmapY;
		extent = this->bitmapHeight;
		p = bitmapY / extent;
		break;
	case 2: // top right corner is anchor
		qd = sqrt(((this->bitmapWidth - bitmapX) * (this->bitmapWidth - bitmapX)) + (bitmapY * bitmapY));
		extent = sqrt((this->bitmapWidth * this->bitmapWidth) + (this->bitmapHeight * this->bitmapHeight));
		p = qd / extent;
		break;
	case 3: // right edge is anchor
		qd = this->bitmapWidth - bitmapX;
		extent = this->bitmapWidth;
		p = qd / extent;
		break;
	case 4: // bottom right corner is anchor
		qd = sqrt(((this->bitmapWidth - bitmapX) * (this->bitmapWidth - bitmapX)) + ((this->bitmapHeight - bitmapY) * (this->bitmapHeight - bitmapY)));
		extent = sqrt((this->bitmapWidth * this->bitmapWidth) + (this->bitmapHeight * this->bitmapHeight));
		p = qd / extent;
		break;
	case 5: // bottom edge is anchor
		qd = this->bitmapHeight - bitmapY;
		extent = this->bitmapHeight;
		p = qd / extent;
		break;
	case 6: // bottom left corner is anchor
		// sqrt of  xpos^2 + (  ) 
		qd = sqrt((bitmapX * bitmapX) + ((this->bitmapHeight - bitmapY) * (this->bitmapHeight - bitmapY)));
		extent = sqrt((this->bitmapWidth * this->bitmapWidth) + (this->bitmapHeight * this->bitmapHeight));
		p = qd / extent;
		break;
	case 7: // left edge is anchor
		qd = bitmapX;
		extent = this->bitmapWidth;
		p = qd / extent;
		break;
	case 8: // center is anchor
		ax = this->bitmapWidth / 2;
		ay = this->bitmapHeight / 2;
		extent = sqrt((ax * ax) + (ay * ay));
		if (bitmapX > ax) {
			if (bitmapY > ay) {
				qd = sqrt(((bitmapX - ax) * (bitmapX - ax)) + ((bitmapY - ay) * (bitmapY - ay)));
			}
			else {
				qd = sqrt(((bitmapX - ax) * (bitmapX - ax)) + ((ay - bitmapY) * (ay - bitmapY)));
			}
		}
		else {
			if (bitmapY > ay) {
				qd = sqrt(((ax - bitmapX) * (ax - bitmapX)) + ((bitmapY - ay) * (bitmapY - ay)));
			}
			else {
				qd = sqrt(((ax - bitmapX) * (ax - bitmapX)) + ((ay - bitmapY) * (ay - bitmapY)));
			}
		}
		p = qd / extent;
		break;
	}
	if (qd == 0) {
		return this->fillB;
	}
	else {
		int gp = (int)(p * 35);
		unsigned char res;
		if (this->mode == 3) {
			// light gradient mode
			if ((int)this->fillB > 215) {

				res = (unsigned char)((int)this->fillB - gp);
			}
			else {
				res = (unsigned char)((int)this->fillB + gp);
			}
		}
		else {
			// dark gradient mode
			if ((int)this->fillB > 35) {
				res = (unsigned char)((int)this->fillB - gp);
			}
			else {
				res = (unsigned char)((int)this->fillB + gp);
			}
		}
		return res;
	}
}
