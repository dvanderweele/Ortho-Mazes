#ifndef CELL_H
#define CELL_H

class Cell {
	private:
		unsigned long long int value;
	public: 
		// getters
		Cell(unsigned long long int = 0x0uLL);
		unsigned long long int getRaw();
		bool isCarved();
		bool isMapBorder();
		bool isEntry();
		bool isExit();
		bool isCanonical();
		bool isHorzNeighbor();
		bool isVertNeighbor();
		bool isDiagNeighbor();
		bool isHorzRoomBorder();
		bool isVertRoomBorder();
		bool isRoomInterior();
		bool isHorzDoor();
		bool isVertDoor();
		bool isHorzWeaveTunnel();
		bool isVertWeaveTunnel();
		bool isNorthWeaveBorder();
		bool isEastWeaveBorder();
		bool isSouthWeaveBorder();
		bool isWestWeaveBorder();
		bool customGet(unsigned long long int);
		// setters
		bool unsafeCustomSet(unsigned long long int);
		bool unsafeCustomUnset(unsigned long long int);
		bool safeCustomSet(unsigned long long int);
		bool safeCustomUnset(unsigned long long int);
		bool setRaw(unsigned long long int);
		bool setCarved();
		bool unsetCarved();
		bool setMapBorder();
		bool unsetMapBorder();
		bool setEntry();
		bool unsetEntry();
		bool setExit();
		bool unsetExit();
		bool setCanonical();
		bool unsetCanonical();
		bool setHorzNeighbor();
		bool unsetHorzNeighbor();
		bool setVertNeighbor();
		bool unsetVertNeighbor();
		bool setDiagNeighbor();
		bool unsetDiagNeighbor();
		bool setHorzRoomBorder();
		bool unsetHorzRoomBorder();
		bool setVertRoomBorder();
		bool unsetVertRoomBorder();
		bool setRoomInterior();
		bool unsetRoomInterior();
		bool setHorzDoor();
		bool unsetHorzDoor();
		bool setVertDoor();
		bool unsetVertDoor();
		bool setHorzWeaveTunnel();
		bool unsetHorzWeaveTunnel();
		bool setVertWeaveTunnel();
		bool unsetVertWeaveTunnel();
		bool setNorthWeaveBorder();
		bool unsetNorthWeaveBorder();
		bool setEastWeaveBorder();
		bool unsetEastWeaveBorder();
		bool setSouthWeaveBorder();
		bool unsetSouthWeaveBorder();
		bool setWestWeaveBorder();
		bool unsetWestWeaveBorder();
};

#endif