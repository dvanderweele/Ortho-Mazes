#include <iostream>

#include "Maze.h"
#include "MazeTest.h"

MazeTest::MazeTest()
{
	runTests();
}

void MazeTest::runTests()
{
	std::cout << "Running tests for Maze Class...\n\n";
	// preliminary tests
	Maze tester1;
	if (tester1.getWidth() == 100uLL) {
		std::cout << "Maze width assigned correctly via default constructor.\n";
		this->passingTests++;
	}
	else {
		std::cout << "Maze width not assigned correctly via default constructor.\n";
		this->failingTests++;
	}
	if (tester1.getHeight() == 100uLL) {
		std::cout << "Maze height assigned correctly via default constructor.\n";
		this->passingTests++;
	}
	else {
		std::cout << "Maze height not assigned correctly via default constructor.\n";
	}
	Maze tester2(10uL, 5uL);
	if (tester2.getWidth() == 10uLL) {
		std::cout << "Maze width assigned correctly when argument passed to constructor.\n";
		this->passingTests++;
	}
	else {
		std::cout << "Maze width not assigned correctly when argument passed to constructor.\n";
		this->failingTests++;
	}
	if (tester2.getHeight() == 5uLL) {
		std::cout << "Maze height assigned correctly when argument passed to constructor.\n";
		this->passingTests++;
	}
	else {
		std::cout << "Maze height not assigned correctly when argument passed to constructor.\n";
		this->failingTests++;
	}
	// end preliminary tests 

	// test grid <---> index conversion functions 
	Maze tester3(8uLL, 6uLL);
	if (tester3.getCellIndex(6uLL, 3uLL) == 21uLL && tester3.getCellIndex(1uLL, 1uLL) == 0uLL
		&& tester3.getCellIndex(1uLL, 4uLL) == 24uLL && tester3.getCellIndex(8uLL, 1uLL) == 7uLL) {
		std::cout << "index numbers are properly calculated from xycoords.\n";
		this->passingTests++;
	}
	else {
		std::cout << "index numbers are not properly calculated from xycoords.\n";
		this->failingTests++;
	}
	if (tester3.getCellXCoord(21uLL) == 6uLL && tester3.getCellXCoord(0uLL) == 1uLL
		&& tester3.getCellXCoord(7uLL) == 8uLL && tester3.getCellXCoord(34uLL) == 3uLL) {
		std::cout << "xcoords properly calculated based on indexes.\n";
		this->passingTests++;
	}
	else {
		std::cout << "xcoords not properly calculated based on indexes.\n";
		this->failingTests++;
	}
	if (tester3.getCellYCoord(21uLL) == 3uLL && tester3.getCellYCoord(0uLL) == 1uLL
		&& tester3.getCellYCoord(24uLL) == 4uLL && tester3.getCellYCoord(7uLL) == 1uLL) {
		std::cout << "ycoords properly calculated based on indexes.\n";
		this->passingTests++;
	}
	else {
		std::cout << "ycoords not properly calculated based on indexes.\n";
		this->failingTests++;
	}
	// end test grid <---> index conversion functions

	// basic cell access tests
	Maze tester4(20uLL, 20uLL);
	if (tester4.mazePtr[tester4.getCellIndex(10uLL, 10uLL)].setCanonical() && tester4.mazePtr[tester4.getCellIndex(10uLL, 10uLL)].isCanonical()) {
		std::cout << "can properly access maze cell member methods.\n";
		this->passingTests++;
	}
	else {
		std::cout << "can't properly access maze cell member methods.\n";
		this->failingTests++;
	}
	// end basic cell access tests

	// end tests
	std::cout << "\nTESTS PASSED: " << this->passingTests << '\n';
	std::cout << "TESTS FAILED: " << this->failingTests << '\n';
}
