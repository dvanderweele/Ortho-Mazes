#include "CellTest.h"

#include <iostream>

#include "Cell.h"

CellTest::CellTest()
{
	runTests();
}

void CellTest::runTests()
{
	std::cout << "Running tests for Cell Class...\n\n";
	// preliminary tests
	if (this->tester.getRaw() == 0x0uLL) {
		std::cout << "Private value initialized correctly via default constructor.\n";
		this->passingTests++;
	}
	else {
		std::cout << "Private value not initialized correctly via default constructor.\n";
		this->failingTests++;
	}
	Cell tester2(0x2uLL);
	if (tester2.getRaw() == 0x2uLL) {
		std::cout << "Private value initialized correctly when argument passed to constructor.\n";
		this->passingTests++;
	}
	else {
		std::cout << "Private value not initialized correctly when argument passed to constructor.\n";
		this->failingTests++;
	}
	if (this->tester.setRaw(0x1uLL) && this->tester.getRaw() == 0x1uLL) {
		std::cout << "setRaw and getRaw working correctly.\n";
		this->passingTests++;
		this->tester.setRaw(0x0uLL);
	}
	else {
		std::cout << "setRaw and getRaw not working correctly.\n";
		this->failingTests++;
	}
	// end preliminary tests 

	// custom bit manipulation function tests
	if (!this->tester.customGet(0x80000uLL)) {
		std::cout << "customGet works when unset bit beyond standard range accessed.\n";
		this->passingTests++;
	}
	else {
		std::cout << "customGet doesn't work when unset bit beyond standard range accessed.\n";
		this->failingTests++;
	}
	if (this->tester.safeCustomSet(0x80000uLL) && this->tester.customGet(0x80000uLL)) {
		std::cout << "safeCustomSet and customGet work on bit beyond standard range.\n";
		this->passingTests++;
	}
	else {
		std::cout << "safeCustomSet and customGet don't work on bit beyond standard range.\n";
		this->failingTests++;
	}
	if (this->tester.safeCustomUnset(0x80000uLL) && !this->tester.customGet(0x80000uLL)) {
		std::cout << "safeCustomUnset and customGet work on bit beyond standard range.\n";
		this->passingTests++;
	}
	else {
		std::cout << "safeCustomUnset and customGet don't work on bit beyond standard range.\n";
		this->failingTests++;
	}
	if (!this->tester.safeCustomSet(0x7FFFFuLL) && !this->tester.safeCustomSet(0x1uLL) && !this->tester.customGet(0x7FFFFuLL) && !this->tester.customGet(0x1uLL)) {
		std::cout << "safeCustomSet properly prevents setting out of bound bits.\n";
		this->passingTests++;
	}
	else {
		std::cout << "safeCustomSet doesn't properly prevent setting out of bound bits.\n";
		this->failingTests++;
	}
	if (this->tester.setCarved() && this->tester.setWestWeaveBorder() && !this->tester.safeCustomUnset(0x1uLL) 
		&& this->tester.isCarved() && !this->tester.safeCustomUnset(0x7FFFFuLL) && this->tester.isWestWeaveBorder()) {
		this->tester.unsetCarved();
		this->tester.unsetWestWeaveBorder();
		std::cout << "safeCustomUnset properly prevents unsetting of out of bound bits that are already set.\n";
		this->passingTests++;
	}
	else {
		std::cout << "safeCustomUnset doesn't properly prevent unsetting of out of bound bits that are already set.\n";
		this->failingTests++;
	}
	this->tester.setRaw(0x0uL);
	if (this->tester.unsafeCustomSet(0x80000uLL) && this->tester.customGet(0x80000uLL)) {
		std::cout << "unsafeCustomSet and customGet work on bit beyond standard range.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsafeCustomSet and customGet don't work on bit beyond standard range.\n";
		this->failingTests++;
	}
	if (this->tester.unsafeCustomUnset(0x80000uLL) && !this->tester.customGet(0x80000uLL)) {
		std::cout << "unsafeCustomUnset and customGet work on bit beyond standard range.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsafeCustomUnset and customGet don't work on bit beyond standard range.\n";
		this->failingTests++;
	}
	if (this->tester.unsafeCustomSet(0x7FFFFuLL) && this->tester.unsafeCustomSet(0x1uLL) 
		&& this->tester.customGet(0x7FFFFuLL) && this->tester.customGet(0x1uLL)) {
		std::cout << "unsafeCustomSet properly sets out of bound bits.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsafeCustomSet doesn't properly set out of bound bits.\n";
		this->failingTests++;
	}
	if (this->tester.setCarved() && this->tester.setWestWeaveBorder() && this->tester.unsafeCustomUnset(0x1uLL)
		&& !this->tester.isCarved() && this->tester.unsafeCustomUnset(0x7FFFFuLL) && !this->tester.isWestWeaveBorder()) {
		std::cout << "unsafeCustomUnset properly unsets of out of bound bits that are already set.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsafeCustomUnset doesn't properly unset out of bound bits that are already set.\n";
		this->failingTests++;
	}
	this->tester.setRaw(0x0uL);

	// end custom bit manipulation function tests

	// bit function tests 

	// carved
	if (this->tester.setCarved() && this->tester.isCarved()) {
		std::cout << "setCarved and isCarved working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setCarved or isCarved not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetCarved() && !this->tester.isCarved()) {
		std::cout << "unsetCarved is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetCarved not working properly\n";
		this->failingTests++;
	}
	// map border
	if (this->tester.setMapBorder() && this->tester.isMapBorder()) {
		std::cout << "setMapBorder and isMapBorder working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setMapBorder or isMapBorder not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetMapBorder() && !this->tester.isMapBorder()) {
		std::cout << "unsetMapBorder is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetMapBorder not working properly\n";
		this->failingTests++;
	}
	// entry
	if (this->tester.setEntry() && this->tester.isEntry()) {
		std::cout << "setEntry and isEntry working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setEntry or isEntry not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetEntry() && !this->tester.isEntry()) {
		std::cout << "unsetEntry is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetEntry not working properly\n";
		this->failingTests++;
	}
	// exit
	if (this->tester.setExit() && this->tester.isExit()) {
		std::cout << "setExit and isExit working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setExit or isExit not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetExit() && !this->tester.isExit()) {
		std::cout << "unsetExit is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetExit not working properly\n";
		this->failingTests++;
	}
	// canonical
	if (this->tester.setCanonical() && this->tester.isCanonical()) {
		std::cout << "setCanonical and isCanonical working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setCanonical or isCanonical not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetCanonical() && !this->tester.isCanonical()) {
		std::cout << "unsetCanonical is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetCanonical not working properly\n";
		this->failingTests++;
	}
	// horizontal neighbor
	if (this->tester.setHorzNeighbor() && this->tester.isHorzNeighbor()) {
		std::cout << "setHorzNeighbor and isHorzNeighbor working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setHorzNeighbor or isHorzNeighbor not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetHorzNeighbor() && !this->tester.isHorzNeighbor()) {
		std::cout << "unsetHorzNeighbor is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetHorzNeighbor not working properly\n";
		this->failingTests++;
	}
	// vertical neighbor
	if (this->tester.setVertNeighbor() && this->tester.isVertNeighbor()) {
		std::cout << "setVertNeighbor and isVertNeighbor working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setVertNeighbor or isVertNeighbor not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetVertNeighbor() && !this->tester.isVertNeighbor()) {
		std::cout << "unsetVertNeighbor is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetVertNeighbor not working properly\n";
		this->failingTests++;
	}
	// diagonal neighbor
	if (this->tester.setDiagNeighbor() && this->tester.isDiagNeighbor()) {
		std::cout << "setDiagNeighbor and isDiagNeighbor working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setDiagNeighbor or isDiagNeighbor not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetDiagNeighbor() && !this->tester.isDiagNeighbor()) {
		std::cout << "unsetDiagNeighbor is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetDiagNeighbor not working properly\n";
		this->failingTests++;
	}
	// horizontal room border
	if (this->tester.setHorzRoomBorder() && this->tester.isHorzRoomBorder()) {
		std::cout << "setHorzRoomBorder and isHorzRoomBorder working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setHorzRoomBorder or isHorzRoomBorder not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetHorzRoomBorder() && !this->tester.isHorzRoomBorder()) {
		std::cout << "unsetHorzRoomBorder is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetHorzRoomBorder not working properly\n";
		this->failingTests++;
	}
	// vertical room border
	if (this->tester.setVertRoomBorder() && this->tester.isVertRoomBorder()) {
		std::cout << "setVertRoomBorder and isVertRoomBorder working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setVertRoomBorder or isVertRoomBorder not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetVertRoomBorder() && !this->tester.isVertRoomBorder()) {
		std::cout << "unsetVertRoomBorder is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetVertRoomBorder not working properly\n";
		this->failingTests++;
	}
	// room interior
	if (this->tester.setRoomInterior() && this->tester.isRoomInterior()) {
		std::cout << "setRoomInterior and isRoomInterior working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setRoomInterior or isRoomInterior not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetRoomInterior() && !this->tester.isRoomInterior()) {
		std::cout << "unsetRoomInterior is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetRoomInterior not working properly\n";
		this->failingTests++;
	}
	// horizontal door
	if (this->tester.setHorzDoor() && this->tester.isHorzDoor()) {
		std::cout << "setHorzDoor and isHorzDoor working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setHorzDoor or isHorzDoor not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetHorzDoor() && !this->tester.isHorzDoor()) {
		std::cout << "unsetHorzdoor is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetHorzDoor not working properly\n";
		this->failingTests++;
	}
	// vertical door
	if (this->tester.setVertDoor() && this->tester.isVertDoor()) {
		std::cout << "setVertDoor and isVertDoor working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setVertDoor or isVertDoor not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetVertDoor() && !this->tester.isVertDoor()) {
		std::cout << "unsetVertdoor is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetVertDoor not working properly\n";
		this->failingTests++;
	}
	// horizontal weave tunnel
	if (this->tester.setHorzWeaveTunnel() && this->tester.isHorzWeaveTunnel()) {
		std::cout << "setHorzWeaveTunnel and isHorzWeaveTunnel working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setHorzWeaveTunnel or isHorzWeaveTunnel not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetHorzWeaveTunnel() && !this->tester.isHorzWeaveTunnel()) {
		std::cout << "unsetHorzWeaveTunnel is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetHorzWeaveTunnel not working properly\n";
		this->failingTests++;
	}
	// vertical weave tunnel
	if (this->tester.setVertWeaveTunnel() && this->tester.isVertWeaveTunnel()) {
		std::cout << "setVertweaveTunnel and isVertWeaveTunnel working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setVertWeaveTunnel or isVertWeaveTunnel not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetVertWeaveTunnel() && !this->tester.isVertWeaveTunnel()) {
		std::cout << "unsetVertWeaveTunnel is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetVertWeaveTunnel not working properly\n";
		this->failingTests++;
	}
	// north weave border
	if (this->tester.setNorthWeaveBorder() && this->tester.isNorthWeaveBorder()) {
		std::cout << "setNorthWeaveBorder and isNorthWeaveBorder working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setNorthWeaveBorder or isNorthWeaveBorder not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetNorthWeaveBorder() && !this->tester.isNorthWeaveBorder()) {
		std::cout << "unsetNorthWeaveBorder is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetNorthWeaveBorder not working properly\n";
		this->failingTests++;
	}
	// east weave border
	if (this->tester.setEastWeaveBorder() && this->tester.isEastWeaveBorder()) {
		std::cout << "setEastWeaveBorder and isEastWeaveBorder working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setEastWeaveBorder or isEastWeaveBorder not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetEastWeaveBorder() && !this->tester.isEastWeaveBorder()) {
		std::cout << "unsetEastWeaveBorder is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetEastWeaveBorder not working properly\n";
		this->failingTests++;
	}
	// south weave border
	if (this->tester.setSouthWeaveBorder() && this->tester.isSouthWeaveBorder()) {
		std::cout << "setSouthWeaveBorder and isSouthWeaveBorder working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setSouthWeaveBorder or isSouthWeaveBorder not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetSouthWeaveBorder() && !this->tester.isSouthWeaveBorder()) {
		std::cout << "unsetSouthWeaveBorder is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetSouthWeaveBorder not working properly\n";
		this->failingTests++;
	}
	// west weave border
	if (this->tester.setWestWeaveBorder() && this->tester.isWestWeaveBorder()) {
		std::cout << "setWestWeaveBorder and isWestWeaveBorder working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "either setWestWeaveBorder or isWestWeaveBorder not working correctly.\n";
		this->failingTests++;
	}
	if (this->tester.unsetWestWeaveBorder() && !this->tester.isWestWeaveBorder()) {
		std::cout << "unsetWestWeaveBorder is working correctly.\n";
		this->passingTests++;
	}
	else {
		std::cout << "unsetWestWeaveBorder not working properly\n";
		this->failingTests++;
	}

	// final test 

	bool integrity = true;
	this->tester.setRaw(0x0uLL);
	if (this->tester.isCarved() || this->tester.isMapBorder() || this->tester.isEntry()
		|| this->tester.isExit() || this->tester.isCanonical() || this->tester.isHorzNeighbor()
		|| this->tester.isVertNeighbor() || this->tester.isDiagNeighbor() || this->tester.isHorzRoomBorder()
		|| this->tester.isVertRoomBorder() || this->tester.isRoomInterior() || this->tester.isHorzDoor()
		|| this->tester.isVertDoor() || this->tester.isHorzWeaveTunnel() || this->tester.isVertWeaveTunnel()
		|| this->tester.isNorthWeaveBorder() || this->tester.isEastWeaveBorder() || this->tester.isSouthWeaveBorder() || this->tester.isWestWeaveBorder()) {
		integrity = false;
	}
	this->tester.setRaw(0x7FFFFuLL);
	if (!this->tester.isCarved() || !this->tester.isMapBorder() || !this->tester.isEntry()
		|| !this->tester.isExit() || !this->tester.isCanonical() || !this->tester.isHorzNeighbor()
		|| !this->tester.isVertNeighbor() || !this->tester.isDiagNeighbor() || !this->tester.isHorzRoomBorder()
		|| !this->tester.isVertRoomBorder() || !this->tester.isRoomInterior() || !this->tester.isHorzDoor()
		|| !this->tester.isVertDoor() || !this->tester.isHorzWeaveTunnel() || !this->tester.isVertWeaveTunnel()
		|| !this->tester.isNorthWeaveBorder() || !this->tester.isEastWeaveBorder() || !this->tester.isSouthWeaveBorder() || !this->tester.isWestWeaveBorder()) {
		integrity = false;
	}
	if (!integrity) {
		std::cout << "Integrity check failed.\n";
		this->failingTests++;
	}
	else {
		std::cout << "Integrity check passed.\n";
		this->passingTests++;
	}
	// end tests
	std::cout << "TESTS PASSED: " << this->passingTests << '\n';
	std::cout << "TESTS FAILED: " << this->failingTests << '\n';
}
