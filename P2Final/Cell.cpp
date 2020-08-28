#include "Cell.h"

Cell::Cell(unsigned long long int val)
{
	setRaw(val);
}

// GETTERS

unsigned long long int Cell::getRaw()
{
	return this->value;
}

bool Cell::isCarved()
{
	bool res = false;
	if ((this->value & 0x1uLL) == 0x1uLL) {
		res = true;
	}
	return res;
}

bool Cell::isMapBorder()
{
	bool res = false;
	if ((this->value & 0x2uLL) == 0x2uLL) {
		res = true;
	}
	return res;
}

bool Cell::isEntry()
{
	bool res = false;
	if ((this->value & 0x4uLL) == 0x4uLL) {
		res = true;
	}
	return res;
}

bool Cell::isExit()
{
	bool res = false;
	if ((this->value & 0x8uLL) == 0x8uLL) {
		res = true;
	}
	return res;
}

bool Cell::isCanonical()
{
	bool res = false;
	if ((this->value & 0x10uLL) == 0x10uLL) {
		res = true;
	}
	return res;
}

bool Cell::isHorzNeighbor()
{
	bool res = false;
	if ((this->value & 0x20uLL) == 0x20uLL) {
		res = true;
	}
	return res;
}

bool Cell::isVertNeighbor()
{
	bool res = false;
	if ((this->value & 0x40uLL) == 0x40uLL) {
		res = true;
	}
	return res;
}

bool Cell::isDiagNeighbor()
{
	bool res = false;
	if ((this->value & 0x80uLL) == 0x80uLL) {
		res = true;
	}
	return res;
}

bool Cell::isHorzRoomBorder()
{
	bool res = false;
	if ((this->value & 0x100uLL) == 0x100uLL) {
		res = true;
	}
	return res;
}

bool Cell::isVertRoomBorder()
{
	bool res = false;
	if ((this->value & 0x200uLL) == 0x200uLL) {
		res = true;
	}
	return res;
}

bool Cell::isRoomInterior()
{
	bool res = false;
	if ((this->value & 0x400uLL) == 0x400uLL) {
		res = true;
	}
	return res;
}

bool Cell::isHorzDoor()
{
	bool res = false;
	if ((this->value & 0x800uLL) == 0x800uLL) {
		res = true;
	}
	return res;
}

bool Cell::isVertDoor()
{
	bool res = false;
	if ((this->value & 0x1000uLL) == 0x1000uLL) {
		res = true;
	}
	return res;
}

bool Cell::isHorzWeaveTunnel()
{
	bool res = false;
	if ((this->value & 0x2000uLL) == 0x2000uLL) {
		res = true;
	}
	return res;
}

bool Cell::isVertWeaveTunnel()
{
	bool res = false;
	if ((this->value & 0x4000uLL) == 0x4000uLL) {
		res = true;
	}
	return res;
}

bool Cell::isNorthWeaveBorder()
{
	bool res = false;
	if ((this->value & 0x8000uLL) == 0x8000uLL) {
		res = true;
	}
	return res;
}

bool Cell::isEastWeaveBorder()
{
	bool res = false;
	if ((this->value & 0x10000uLL) == 0x10000uLL) {
		res = true;
	}
	return res;
}

bool Cell::isSouthWeaveBorder()
{
	bool res = false;
	if ((this->value & 0x20000uLL) == 0x20000uLL) {
		res = true;
	}
	return res;
}

bool Cell::isWestWeaveBorder()
{
	bool res = false;
	if ((this->value & 0x40000uLL) == 0x40000uLL) {
		res = true;
	}
	return res;
}

bool Cell::customGet(unsigned long long int val) {
	bool res = false;
	if ((this->value & val) == val) {
		res = true;
	}
	return res;
}

// SETTERS

bool Cell::unsafeCustomSet(unsigned long long int val) {
	this->value = this->value | val;
	return true;
}
bool Cell::unsafeCustomUnset(unsigned long long int val) {
	this->value = this->value & ~val;
	return true;
}
bool Cell::safeCustomSet(unsigned long long int val) {
	bool res = false;
	if (val > 0x7FFFF) {
		res = true;
		this->value = this->value | val;
	}
	return res;
}
bool Cell::safeCustomUnset(unsigned long long int val) {
	bool res = false;
	if (val > 0x7FFFF) {
		res = true;
		this->value = this->value & ~val;
	}
	return res;
}

bool Cell::setRaw(unsigned long long int newVal)
{
	this->value = newVal;
	return true;
}

bool Cell::setCarved()
{
	this->value = this->value | 0x1uLL;
	return true;
}

bool Cell::unsetCarved()
{
	this->value = this->value & ~0x1uLL;
	return true;
}

bool Cell::setMapBorder()
{
	this->value = this->value | 0x2uLL;
	return true;
}

bool Cell::unsetMapBorder()
{
	this->value = this->value & ~0x2uLL;
	return true;
}

bool Cell::setEntry()
{
	this->value = this->value | 0x4uLL;
	return true;
}

bool Cell::unsetEntry()
{
	this->value = this->value & ~0x4uLL;
	return true;
}

bool Cell::setExit()
{
	this->value = this->value | 0x8uLL;
	return true;
}

bool Cell::unsetExit()
{
	this->value = this->value & ~0x8uLL;
	return true;
}

bool Cell::setCanonical()
{
	this->value = this->value | 0x10uLL;
	return true;
}

bool Cell::unsetCanonical()
{
	this->value = this->value & ~0x10uLL;
	return true;
}

bool Cell::setHorzNeighbor()
{
	this->value = this->value | 0x20uLL;
	return true;
}

bool Cell::unsetHorzNeighbor()
{
	this->value = this->value & ~0x20uLL;
	return true;
}

bool Cell::setVertNeighbor()
{
	this->value = this->value | 0x40uLL;
	return true;
}

bool Cell::unsetVertNeighbor()
{
	this->value = this->value & ~0x40uLL;
	return true;
}

bool Cell::setDiagNeighbor()
{
	this->value = this->value | 0x80uLL;
	return true;
}

bool Cell::unsetDiagNeighbor()
{
	this->value = this->value & ~0x80uLL;
	return true;
}

bool Cell::setHorzRoomBorder()
{
	this->value = this->value | 0x100uLL;
	return true;
}

bool Cell::unsetHorzRoomBorder()
{
	this->value = this->value & ~0x100uLL;
	return true;
}

bool Cell::setVertRoomBorder()
{
	this->value = this->value | 0x200uLL;
	return true;
}

bool Cell::unsetVertRoomBorder()
{
	this->value = this->value & ~0x200uLL;
	return true;
}

bool Cell::setRoomInterior()
{
	this->value = this->value | 0x400uLL;
	return true;
}

bool Cell::unsetRoomInterior()
{
	this->value = this->value & ~0x400uLL;
	return true;
}

bool Cell::setHorzDoor()
{
	this->value = this->value | 0x800uLL;
	return true;
}

bool Cell::unsetHorzDoor()
{
	this->value = this->value & ~0x800uLL;
	return true;
}

bool Cell::setVertDoor()
{
	this->value = this->value | 0x1000uLL;
	return true;
}

bool Cell::unsetVertDoor()
{
	this->value = this->value & ~0x1000uLL;
	return true;
}

bool Cell::setHorzWeaveTunnel()
{
	this->value = this->value | 0x2000uLL;
	return true;
}

bool Cell::unsetHorzWeaveTunnel()
{
	this->value = this->value & ~0x2000uLL;
	return true;
}

bool Cell::setVertWeaveTunnel()
{
	this->value = this->value | 0x4000uLL;
	return true;
}

bool Cell::unsetVertWeaveTunnel()
{
	this->value = this->value & ~0x4000uLL;
	return true;
}

bool Cell::setNorthWeaveBorder()
{
	this->value = this->value | 0x8000uLL;
	return true;
}

bool Cell::unsetNorthWeaveBorder()
{
	this->value = this->value & ~0x8000uLL;
	return true;
}

bool Cell::setEastWeaveBorder()
{
	this->value = this->value | 0x10000uLL;
	return true;
}

bool Cell::unsetEastWeaveBorder()
{
	this->value = this->value & ~0x10000uLL;
	return true;
}

bool Cell::setSouthWeaveBorder()
{
	this->value = this->value | 0x20000uLL;
	return true;
}

bool Cell::unsetSouthWeaveBorder()
{
	this->value = this->value & ~0x20000uLL;
	return true;
}

bool Cell::setWestWeaveBorder()
{
	this->value = this->value | 0x40000uLL;
	return true;
}

bool Cell::unsetWestWeaveBorder()
{
	this->value = this->value & ~0x40000uLL;
	return true;
}
