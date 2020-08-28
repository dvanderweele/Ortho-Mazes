#include <iostream>
#include <string>

#include "RecursiveBacktracker.h"
#include "RbRecursiveBacktracker.h"
#include "WvRecursiveBacktracker.h"
#include "RbWvRecursiveBacktracker.h"
#include "Maze.h"
#include "Renderer.h"
#include "RbRenderer.h"

using namespace std;

void printAlgoList();
void printAppHeader();
void printMainMenuInstructions();
void parseUserInput(string, int&);
void renderDescription(int, int &);
void bootstrapAlgorithm(int, int &);
void recurseStatic();
void recursePoly();
void weaveStatic();
void weavePoly();

int main() {

	printAppHeader();
	system("cls");

	/*
		To manage the state of the main outer shell of the program, a simplistic state machine will be used. 
		States: 
			0 - Waiting for user to enter a valid main menu option.
			1 - Parsing and validating user's entered main menu option.
			2 - Viewing details about an algorithm.
			3 - Running an algorithm.
			4 - Quitting.

			State 0 can only go to State 1. 

			State 1 can go to either State 2, State 3, or State 4. 

			State's 2 and 3 will both eventually return to State 0.

			State 4 is used as a flag to break out of main program loop and end the program. Therefore, 
			it cannot navigate to any other states.
	*/

	int mainMenuState = 0;
	string userInput;

	while (mainMenuState != 4) {
		printAlgoList();
		printMainMenuInstructions();
		userInput.clear();
		getline(cin, userInput);
		parseUserInput(userInput, mainMenuState);
		system("cls");
	}

	return 0;
}

void printAppHeader() {
	cout << "   __    ____    _____   _   _    __             ___      ____       ___       _______     _____       __           " << endl;
	cout << "  /  \\  |  _ \\  |_   _| | | | |  /  \\           |   \\    /    |     /    \\    |___    |   |  ___|     /  \\    " << endl;
	cout << " /    \\ | |/ /    | |   | |_| | /    \\   ___    | |\\ \\  /  /| |    /  /\\  \\      /   /    | |_       |  |\\|  " << endl;
	cout << " | || | |   |     | |   |  _  | | || |  |___|   | | \\ \\/  / | |   |   __   |    /   /     |  _|       \\  \\      " << endl;
	cout << " \\    / | |\\ \\    | |   | | | | \\    /          | |  \\   /  | |   |  |  |  |   /   /__    | |____  |\\__\\  |  " << endl;
	cout << "  \\__/  |_| \\_\\   |_|   |_| |_|  \\__/           |_|   \\_/   |_|   |__|  |__|  |_______|   |______|  \\____/    " << endl;

	cout << "\n************************************************************************************************************" << endl;

	cout << "\nA fun tool for generating orthogonal mazes via a range of algorithms. Version 0.1.\n\n";
	cout << "Note: this program makes use of 'system('cls') calls to improve the user experience.\n";
	cout << "If you are using this program on a system (i.e. not a modern version of Windows) that\n";
	cout << "does not support 'system('cls')' calls, then let me know and I can provide a version\n";
	cout << "of the program that does not make use of such functionality.\n\n";
	cout << "By Dave VanderWeele.\n\n";
	cout << "To continue, press Enter.";
	cin.get();
}

void printAlgoList() {
	cout << "   *************************************************** " << endl;
	cout << "   *      ALGORITHM                       *  NUMBER  * " << endl;
	cout << "   *************************************************** " << endl;
	cout << "   * Recursive Backtracker - Static Color *     1    * " << endl;
	cout << "   *************************************************** " << endl;
	cout << "   * Recursive BackTracker - Polychrome   *     2    * " << endl;
	cout << "   *************************************************** " << endl;
	cout << "   * Weave Re. Backtracker - Static Color *     3    * " << endl;
	cout << "   *************************************************** " << endl;
	cout << "   * Weave Re. Backtracker - Polychrome   *     4    * " << endl;
	cout << "   *************************************************** " << endl;
}

void printMainMenuInstructions() {
	cout << "\n\n";
	cout << "   **************************************************************************************************** " << endl;
	cout << "   *                                         MENU INSTRUCTIONS                                        * " << endl;
	cout << "   **************************************************************************************************** " << endl;
	cout << "   *   View Algorithm Details   * type: about [algorithm number][ENTER] *   example: about 1[ENTER]   * " << endl;
	cout << "   **************************************************************************************************** " << endl;
	cout << "   *   Run an Algorithm         * type: run [algorithm number][ENTER]   *   example: run 1[ENTER]     * " << endl;
	cout << "   **************************************************************************************************** " << endl;
	cout << "   *   Quit                     * type: quit                            *   example: quit             * " << endl;
	cout << "   **************************************************************************************************** " << endl;
	cout << "\nWhat would you like to do? ";
}

void parseUserInput(string userInput, int &menuState) {
	menuState = 1;
	system("cls");
	if (userInput == "quit" || userInput == "Quit" || userInput == "q" || userInput == "Q") {
		menuState = 4;
	}
	else if (userInput.size() >= 5) {
		if (userInput.substr(0,4) == "run ") {
			switch (userInput.at(4)) {
			case '1': 
				bootstrapAlgorithm(1, menuState);
				break;
			case '2':
				bootstrapAlgorithm(2, menuState);
				break;
			case '3':
				bootstrapAlgorithm(3, menuState);
				break;
			case '4':
				bootstrapAlgorithm(4, menuState);
				break;
			default: 
				cout << "\nError! You've entered an invalid algorithm number. Try again.\n\n";
			}
		}
		else if (userInput.size() >= 6 && userInput.substr(0, 6) == "about ") {
			switch (userInput.at(6)) {
			case '1':
				renderDescription(1, menuState);
				break;
			case '2':
				renderDescription(2, menuState);
				break;
			case '3':
				renderDescription(3, menuState);
				break;
			case '4':
				renderDescription(4, menuState);
				break;
			default:
				cout << "\nError! You've entered an invalid algorithm number. Try again.\n\n";
			}
		}
		else {
			cout << "\nError! You've entered an invalid command. Try again.\n\n";
		}
	}
	else {
		cout << "\nError! You've entered an invalid command. Try again.\n\n";
	}
}

void renderDescription(int algoNum, int & menuState) {
	menuState = 2;
	switch (algoNum) {
	case 1:
		cout << "RECURSIVE BACKTRACKER - STATIC COLOR\n\n";
		cout << "Recursive Backtracking is one of the most famous maze generation algorithms.\n";
		cout << "Recursive Backtracking is not the most efficient algorithm ever invented, but\n";
		cout << "it is quite flexible and easy to implement. In my implementation, there are \n";
		cout << "several configurable options: you can configure the size of the maze; you can\n";
		cout << "also configure the maze's 'bias' or whether and how much you want corridors to \n";
		cout << "prefer to continue mostly uninterrupted in horizontal or vertical orientations;\n";
		cout << "you can also give the algorithm a chance to randomly invert the bias during the \n";
		cout << "course of carving the maze; you can configure how you want maze entrance and exits\n";
		cout << "generated.\n\n";
		cout << "An important property of the mazes generated via this algorithm is that, unless\n";
		cout << "you explicitly tell the algorithm to carve loops, the maze will be perfect in the\n";
		cout << "sense that the outputted maze will always possess exactly one path from any one\n";
		cout << "point in the maze to any other point in the maze.\n\n";
		cout << "In this version of the recursive backtracker, you can provide 4 different RGB colors\n";
		cout << "to be used in rendering the maze.\n\n";
		break;
	case 2:
		cout << "RECURSIVE BACKTRACKER - POLYCHROME\n\n";
		cout << "Recursive Backtracking is one of the most famous maze generation algorithms.\n";
		cout << "Recursive Backtracking is not the most efficient algorithm ever invented, but\n";
		cout << "it is quite flexible and easy to implement. In my implementation, there are \n";
		cout << "several configurable options: you can configure the size of the maze; you can\n";
		cout << "also configure the maze's 'bias' or whether and how much you want corridors to \n";
		cout << "prefer to continue mostly uninterrupted in horizontal or vertical orientations;\n";
		cout << "you can also give the algorithm a chance to randomly invert the bias during the \n";
		cout << "course of carving the maze; you can configure how you want maze entrance and exits\n";
		cout << "generated.\n\n";
		cout << "An important property of the mazes generated via this algorithm is that, unless\n";
		cout << "you explicitly tell the algorithm to carve loops, the maze will be perfect in the\n";
		cout << "sense that the outputted maze will always possess exactly one path from any one\n";
		cout << "point in the maze to any other point in the maze.\n\n";
		cout << "In this version of the recursive backtracker, 'area codes' are encoded into the\n";
		cout << "cells and incremented every so often so that during the rendering, different \n";
		cout << "'polychrome' or multicolored effects are produced in the final image of the maze.\n\n";
		break;
	case 3:
		cout << "WEAVING RECURSIVE BACKTRACKER - STATIC COLOR\n\n";
		cout << "This type of maze is much like the RECURSIVE BACKTRACKER - STATIC COLOR maze.\n";
		cout << "However, an important difference is that this version of the algorithm creates\n";
		cout << "a '2.5D' version of the maze where corridors have the ability to 'tunnel' beneath\n";
		cout << "other corridors.\n\n";
		cout << "Recursive Backtracking is one of the most famous maze generation algorithms.\n";
		cout << "Recursive Backtracking is not the most efficient algorithm ever invented, but\n";
		cout << "it is quite flexible and easy to implement. In my implementation, there are \n";
		cout << "several configurable options: you can configure the size of the maze; you can\n";
		cout << "also configure the maze's 'bias' or whether and how much you want corridors to \n";
		cout << "prefer to continue mostly uninterrupted in horizontal or vertical orientations;\n";
		cout << "you can also give the algorithm a chance to randomly invert the bias during the \n";
		cout << "course of carving the maze; you can configure how you want maze entrance and exits\n";
		cout << "generated.\n\n";
		cout << "An important property of the mazes generated via this algorithm is that, unless\n";
		cout << "you explicitly tell the algorithm to carve loops, the maze will be perfect in the\n";
		cout << "sense that the outputted maze will always possess exactly one path from any one\n";
		cout << "point in the maze to any other point in the maze.\n\n";
		cout << "In this version of the recursive backtracker, you can provide 4 different RGB colors\n";
		cout << "to be used in rendering the maze.\n\n";
		break;
	case 4:
		cout << "WEAVING RECURSIVE BACKTRACKER - POLYCHROME\n\n";
		cout << "This type of maze is much like the RECURSIVE BACKTRACKER - POLYCHROME maze.\n";
		cout << "However, an important difference is that this version of the algorithm creates\n";
		cout << "a '2.5D' version of the maze where corridors have the ability to 'tunnel' beneath\n";
		cout << "other corridors.\n\n";
		cout << "Recursive Backtracking is one of the most famous maze generation algorithms.\n";
		cout << "Recursive Backtracking is not the most efficient algorithm ever invented, but\n";
		cout << "it is quite flexible and easy to implement. In my implementation, there are \n";
		cout << "several configurable options: you can configure the size of the maze; you can\n";
		cout << "also configure the maze's 'bias' or whether and how much you want corridors to \n";
		cout << "prefer to continue mostly uninterrupted in horizontal or vertical orientations;\n";
		cout << "you can also give the algorithm a chance to randomly invert the bias during the \n";
		cout << "course of carving the maze; you can configure how you want maze entrance and exits\n";
		cout << "generated.\n\n";
		cout << "An important property of the mazes generated via this algorithm is that, unless\n";
		cout << "you explicitly tell the algorithm to carve loops, the maze will be perfect in the\n";
		cout << "sense that the outputted maze will always possess exactly one path from any one\n";
		cout << "point in the maze to any other point in the maze.\n\n";
		cout << "In this version of the recursive backtracker, 'area codes' are encoded into the\n";
		cout << "cells and incremented every so often so that during the rendering, different \n";
		cout << "'polychrome' or multicolored effects are produced in the final image of the maze.\n\n";
		break;
	}
	cout << "Press Enter to go back to the Main Menu. ";
	cin.get();
	menuState = 0;
	system("cls");
}

void bootstrapAlgorithm(int algoNum, int& menuState) {
	menuState = 3;
	switch (algoNum) {
	case 1:
		system("cls");
		recurseStatic();
		break;
	case 2:
		system("cls");
		recursePoly();
		break;
	case 3:
		system("cls");
		weaveStatic();
		break;
	case 4:
		system("cls");
		weavePoly();
		break;
	}
	cout << "Press Enter to go back to the Main Menu. ";
	cin.get();
	menuState = 0;
	system("cls");
}

void recurseStatic() {
	cout << "Let's get some information about how you want the Recursive Backtracker to generate and render your maze!\n\n";
	int startEdge;
	cout << "You can have the entrance for the maze placed randomly in one of five areas of the maze:\n";
	cout << "0 - Top Edge\n";
	cout << "1 - Right Edge\n";
	cout << "2 - Bottom Edge\n";
	cout << "3 - Left Edge\n";
	cout << "4 - Inside the Maze\n";
	cout << "Please enter the number corresponding to area you want the maze to start and press Enter: ";
	cin >> startEdge;
	system("cls");
	int endEdge;
	cout << "You can have the exit for the maze placed randomly in one of five areas of the maze:\n";
	cout << "0 - Top Edge\n";
	cout << "1 - Right Edge\n";
	cout << "2 - Bottom Edge\n";
	cout << "3 - Left Edge\n";
	cout << "4 - Inside the Maze\n";
	cout << "Please enter the number corresponding to area you want the maze to end and press Enter: ";
	cin >> endEdge;
	system("cls");
	float bias;
	cout << "'Bias' is when maze corridors tend to prefer either horizontal or vertical directions.\n";
	cout << "Whether there is a horizontal, vertical, or even bias affects the overall 'texture' of the maze.\n";
	cout << "To configure the bias, please enter a decimal or floating point number ranging from 0 to 1 inclusive.\n";
	cout << "If you want an 'even' bias, simply enter 0.5. For more horizontal bias, enter a number closer to 1.\n";
	cout << "For more vertical bias, enter a number closer to 0. Enter your bias and press Enter: ";
	cin >> bias;
	system("cls");
	cout << "To create interesting visual effects, you can ask the backtracker to randomly 'invert' the bias\n";
	cout << "that you just configured. If you would like the backtracker to randomly 'invert' the bias, enter 1.\n";
	cout << "If you don't want the backtracker to randomly 'invert' the bias, enter 0 and press Enter: ";
	int invertInput;
	cin >> invertInput;
	bool invert;
	if (invertInput == 1)
		invert = true;
	else
		invert = false;
	float inversionChance = 0.02f;
	if (invert) {
		int configureInput;
		bool configure = false;
		cout << "\nSince you chose to have the backtracker randomly invert the bias, you have an opportunity to\n";
		cout << "configure the actual chance that the backtracker has to randomly invert the bias during each\n";
		cout << "loop of the generation process. Warning: this is a finicky parameter for advanced usage only.\n";
		cout << "If you provide too high of a chance, the bias will invert too often, nullifying your earlier\n";
		cout << "bias preference that you provided. By default, the inversion chance is set to .02. Would you\n";
		cout << "like to manually configure the inversion chance? Enter 1 for yes, 0 for no, and press Enter: ";
		cin >> configureInput;
		if (configureInput == 1)
			configure = true;
		if (configure) {
			cout << "Please provide a decimal or floating point value for the inversion chance between 0 and 1 exclusive, and press Enter: ";
			cin >> inversionChance;
		}
	}
	system("cls");
	int loopsInput;
	bool loops = false;
	cout << "By default, a recursive backtracker maze does not have any loops. This means there is exactly one\n";
	cout << "path from anyone point in the maze to any other point. However, if you would like the maze to carve\n";
	cout << "a few loops at the end of the process for fun, enter 1. Otherwise, enter 0 and press Enter: ";
	cin >> loopsInput;
	if (loopsInput == 1)
		loops = true;
	system("cls");
	cout << "You need to decide how big you want your maze. Due to the admittedly opinionated graph model utilized\n";
	cout << "by the algorithm, you must specify both the width and height of your maze in odd numbers. It's okay\n";
	cout << "if you enter an even number, as in that case your preference will be truncated to the nearest odd number.\n";
	cout << "Also, for your first time, a suggested starting point is 101 wide and 101 high.\n";
	cout << "How many cells wide do you want your maze [then press Enter]: ";
	unsigned long long width;
	cin >> width;
	if (width < 1)
		width = 1uLL;
	if (width % 2 == 0)
		width -= 1;
	cout << "How many cells high do you want your maze [then press Enter]: ";
	unsigned long long height;
	cin >> height;
	if (height < 1)
		height = 1uLL;
	if (height % 2 == 0)
		height -= 1;
	system("cls");
	cout << "An image of your maze will be generated in PPM file format. This is an older, inefficient (space-wise)\n";
	cout << "file format, but it is used for convenience due to the difficulty of programmatically manipulating PNG and\n";
	cout << "JPG files. After your file is generated, your system's default image viewing application may not know what\n";
	cout << "to do with the image file. Rest assured, however, that it is easy to view and convert (i.e. to PNG, PDF, etc)\n";
	cout << "PPM image files in freely available image manipulation software such as LibreOffice Draw or GIMP.\n\n";
	cout << "You can now configure the dimension in pixels of your rendered maze image.\n";
	cout << "The suggested starting point (to avoid accidentally generating too large of an image) is 10 pixels for\n";
	cout << "the dimension for each cell in your maze and 10 pixels of margin space. In the case of cells in your maze,\n";
	cout << "a choice of '10' will indicate that every cell in your maze will be 10 pixels wide and 10 pixels tall.\n";
	cout << "In the case of margin, a choice of '10' will indicate a margin 10 pixels wide on all sides of your maze image.\n\n";
	int cellPixels;
	int marginPixels;
	cout << "How many pixels do you want for your maze cells (again, 10 is suggested for first-timers) [then press Enter]: ";
	cin >> cellPixels;
	cout << "How many pixels wide do you want the margin of your maze image to be [then press Enter]: ";
	cin >> marginPixels;
	system("cls");
	cout << "You can configure the colors in which your maze image is rendered by specifying standard RGB color values\n";
	cout << "ranging from 0 to 255. There are five different colors for you to configure: \n\n";
	int fillR, fillG, fillB, carveR, carveG, carveB, margR, margG, margB, startR, startG, startB, endR, endG, endB;
	cout << "Fill Color - for pixels in filled portions of maze (suggested RGB: 44,  82, 130 = dark blue)\n";
	cout << "Carve Color - for pixels in carved portions of maze (suggested RGB: 180, 210, 230 = light blue)\n";
	cout << "Start Color - for pixels in maze's starting cell (suggested RGB: 0, 210,   0 = green)\n";
	cout << "End Color - for pixels in maze's ending cell (suggested RGB: 210,   0,   0 = salmon)\n";
	cout << "Margin Color - for pixels in margin of maze image (suggested RGB: 255, 255, 255 = white)\n\n";
	cout << "You will now enter each of the three RGB color values one at a time separately for each of the\n";
	cout << "five colors. DO NOT enter more than one numeric value (e.g. for red and green) on the same line.\n\n";
	cout << "Red Fill Value [then press Enter]: ";
	cin >> fillR;
	cout << "Green Fill Value [then press Enter]: ";
	cin >> fillG;
	cout << "Blue Fill Value [then press Enter]: ";
	cin >> fillB;
	cout << "Red Carve Value [then press Enter]: ";
	cin >> carveR;
	cout << "Green Carve Value [then press Enter]: ";
	cin >> carveG;
	cout << "Blue Carve Value [then press Enter]: ";
	cin >> carveB;
	cout << "Red Start Value [then press Enter]: ";
	cin >> startR;
	cout << "Green Start Value [then press Enter]: ";
	cin >> startG;
	cout << "Blue Start Value [then press Enter]: ";
	cin >> startB;
	cout << "Red Exit Value [then press Enter]: ";
	cin >> endR;
	cout << "Green Exit Value [then press Enter]: ";
	cin >> endG;
	cout << "Blue Exit Value [then press Enter]: ";
	cin >> endB;
	cout << "Red Margin Value [then press Enter]: ";
	cin >> margR;
	cout << "Green Margin Value [then press Enter]: ";
	cin >> margG;
	cout << "Blue Margin Value [then press Enter]: ";
	cin >> margB;
	system("cls");
	cout << "Your maze will soon start generating.\n";
	cin.get();
	string filename;
	cout << "Please enter a filename (without an extension, as that will be added automatically) for your image [then press Enter]: ";
	getline(cin, filename);
	filename.append(".ppm");
	cout << "Press enter to confirm and start the maze generation process.\n";
	cin.get();
	Maze maze = Maze(width, height, 0x0000000000000000uLL);
	cout << "Generating...\n";
	RecursiveBacktracker rb = RecursiveBacktracker(maze, startEdge, endEdge, bias, invert, inversionChance, loops);
	cout << "Done generating maze. Starting image rendering process.\n";
	Renderer renderer = Renderer(maze, filename, marginPixels, cellPixels, fillR, fillG, fillB, carveR, carveG, carveB, 
		startR, startG, startB, endR, endG, endB, margR, margG, margB);
	cout << "Done rendering image file " << filename << ".\n";
}

void recursePoly() {
	cout << "Let's get some information about how you want the Polychrome Recursive Backtracker to generate and render your maze!\n\n";
	int startEdge;
	cout << "You can have the entrance for the maze placed randomly in one of five areas of the maze:\n";
	cout << "0 - Top Edge\n";
	cout << "1 - Right Edge\n";
	cout << "2 - Bottom Edge\n";
	cout << "3 - Left Edge\n";
	cout << "4 - Inside the Maze\n";
	cout << "Please enter the number corresponding to area you want the maze to start [then press Enter]: ";
	cin >> startEdge;
	system("cls");
	int endEdge;
	cout << "You can have the exit for the maze placed randomly in one of five areas of the maze:\n";
	cout << "0 - Top Edge\n";
	cout << "1 - Right Edge\n";
	cout << "2 - Bottom Edge\n";
	cout << "3 - Left Edge\n";
	cout << "4 - Inside the Maze\n";
	cout << "Please enter the number corresponding to area you want the maze to end [then press Enter]: ";
	cin >> endEdge;
	system("cls");
	float bias;
	cout << "'Bias' is when maze corridors tend to prefer either horizontal or vertical directions.\n";
	cout << "Whether there is a horizontal, vertical, or even bias affects the overall 'texture' of the maze.\n";
	cout << "To configure the bias, please enter a decimal or floating point number ranging from 0 to 1 inclusive.\n";
	cout << "If you want an 'even' bias, simply enter 0.5. For more horizontal bias, enter a number closer to 1.\n";
	cout << "For more vertical bias, enter a number closer to 0. Enter your bias [then press Enter]: ";
	cin >> bias;
	system("cls");
	cout << "To create interesting visual effects, you can ask the backtracker to randomly 'invert' the bias\n";
	cout << "that you just configured. If you would like the backtracker to randomly 'invert' the bias, enter 1.\n";
	cout << "If you don't want the backtracker to randomly 'invert' the bias, enter 0 [then press Enter]: ";
	int invertInput;
	cin >> invertInput;
	bool invert;
	if (invertInput == 1)
		invert = true;
	else
		invert = false;
	float inversionChance = 0.02f;
	if (invert) {
		int configureInput;
		bool configure = false;
		cout << "\nSince you chose to have the backtracker randomly invert the bias, you have an opportunity to\n";
		cout << "configure the actual chance that the backtracker has to randomly invert the bias during each\n";
		cout << "loop of the generation process. Warning: this is a finicky parameter for advanced usage only.\n";
		cout << "If you provide too high of a chance, the bias will invert too often, nullifying your earlier\n";
		cout << "bias preference that you provided. By default, the inversion chance is set to .02. Would you\n";
		cout << "like to manually configure the inversion chance? Enter 1 for yes, 0 for no [then press Enter]: ";
		cin >> configureInput;
		if (configureInput == 1)
			configure = true;
		if (configure) {
			cout << "Please provide a decimal or floating point value for the inversion chance between 0 and 1 exclusive [then press Enter]: ";
			cin >> inversionChance;
		}
	}
	system("cls");
	int loopsInput;
	bool loops = false;
	cout << "By default, a recursive backtracker maze does not have any loops. This means there is exactly one\n";
	cout << "path from anyone point in the maze to any other point. However, if you would like the maze to carve\n";
	cout << "a few loops at the end of the process for fun, enter 1. Otherwise, enter 0 [then press Enter]: ";
	cin >> loopsInput;
	if (loopsInput == 1)
		loops = true;
	system("cls");
	cout << "You need to decide how big you want your maze. Due to the admittedly opinionated graph model utilized\n";
	cout << "by the algorithm, you must specify both the width and height of your maze in odd numbers. It's okay\n";
	cout << "if you enter an even number, as in that case your preference will be truncated to the nearest odd number.\n";
	cout << "Also, for your first time, a suggested starting point is 101 wide and 101 high.\n";
	cout << "How many cells wide do you want your maze: ";
	unsigned long long width;
	cin >> width;
	if (width < 1)
		width = 1uLL;
	if (width % 2 == 0)
		width -= 1;
	cout << "How many cells high do you want your maze: ";
	unsigned long long height;
	cin >> height;
	if (height < 1)
		height = 1uLL;
	if (height % 2 == 0)
		height -= 1;
	system("cls");
	cout << "An image of your maze will be generated in PPM file format. This is an older, inefficient (space-wise)\n";
	cout << "file format, but it is used for convenience due to the difficulty of programmatically manipulating PNG and\n";
	cout << "JPG files. After your file is generated, your system's default image viewing application may not know what\n";
	cout << "to do with the image file. Rest assured, however, that it is easy to view and convert (i.e. to PNG, PDF, etc)\n";
	cout << "PPM image files in freely available image manipulation software such as LibreOffice Draw or GIMP.\n\n";
	cout << "You can now configure the dimension in pixels of your rendered maze image.\n";
	cout << "The suggested starting point (to avoid accidentally generating too large of an image) is 10 pixels for\n";
	cout << "the dimension for each cell in your maze and 10 pixels of margin space. In the case of cells in your maze,\n";
	cout << "a choice of '10' will indicate that every cell in your maze will be 10 pixels wide and 10 pixels tall.\n";
	cout << "In the case of margin, a choice of '10' will indicate a margin 10 pixels wide on all sides of your maze image.\n\n";
	int cellPixels;
	int marginPixels;
	cout << "How many pixels do you want for your maze cells (again, 10 is suggested for first-timers) [then press Enter]: ";
	cin >> cellPixels;
	cout << "How many pixels wide do you want the margin of your maze image to be [then press Enter]: ";
	cin >> marginPixels;
	system("cls");
	cout << "This maze image renderer will dynamically pick the colors of your maze for you with a little configuration.\n";
	cout << "First, you need to specify the RGB color values (for the margin of your rendered maze image)\n";
	cout << "ranging from 0 to 255. Suggested RGB values: 255, 255, 255 = white\n\n";
	int margR, margG, margB;
	cout << "You will now enter each of the three RGB color values one at a time separately for the\n";
	cout << "margin color. DO NOT enter more than one numeric value (e.g. for red and green) on the same line.\n\n";
	cout << "Red Margin Value [then press Enter]: ";
	cin >> margR;
	cout << "Green Margin Value [then press Enter]: ";
	cin >> margG;
	cout << "Blue Margin Value [then press Enter]: ";
	cin >> margB;
	system("cls");
	int mode;
	cout << "There are four different polychrome rendering modes for you to choose from: \n";
	cout << "1 - static, light fill color and dark carve color are both randomly chosen.\n";
	cout << "2 - static, dark fill color and light carve color are both randomly chosen.\n";
	cout << "3 - dynamic, light fill color and dark carve color randomly chosen, randomly changed.\n";
	cout << "4 - dynamic, dark fill color and light carve color randomly chosen, randomly changed.\n";
	cout << "Your maze will soon start generating.\n";
	cout << "Please enter the number of the polychrome rendering mode you want [then press Enter]: ";
	cin >> mode;
	system("cls");
	int anchor = 0;
	float areaCodeIncChance = .005f;
	if (mode == 3 || mode == 4) {
		cout << "Since you chose a dynamic polychrome rendering mode, just a few more questions.\n\n";
		cout << "Please configure the chance you wish the generation process to have to change colors\n";
		cout << "during the rendering loop. The default chance is .005. This is a finicky parameter,\n";
		cout << "so it is advised for beginners to simply stick with that default value of .005.\n\n";
		cout << "Enter a decimal or floating point value between 0 and 1 exclusive [then press Enter]: ";
		cin >> areaCodeIncChance;
		cout << "\nYou must choose an 'anchoring' point for the background color gradient that the\n";
		cout << "renderer generates: \n\n";
		cout << "0 - Top Left Corner\n";
		cout << "1 - Top Edge\n";
		cout << "2 - Top Right Corner\n";
		cout << "3 - Right Edge\n";
		cout << "4 - Bottom Right Corner\n";
		cout << "5 - Bottom Edge\n";
		cout << "6 - Bottom Left Corner\n";
		cout << "7 - Left Edge\n";
		cout << "8 - Image Center\n\n";
		cout << "Please enter the number of the anchoring point you want [then press Enter]: ";
		cin >> anchor;
	}
	system("cls");
	cin.get();
	string filename;
	cout << "Please enter a filename (without an extension, as that will be added automatically) for your image [then press Enter]: ";
	getline(cin, filename);
	filename.append(".ppm");
	cout << "Press enter to confirm and start the maze generation process.\n";
	cin.get();
	Maze maze = Maze(width, height, 0x0000000000000000uLL);
	cout << "Generating...\n";
	RbRecursiveBacktracker rb = RbRecursiveBacktracker(maze, startEdge, endEdge, bias, invert, inversionChance, areaCodeIncChance, loops);
	cout << "Done generating maze. Starting image rendering process.\n";
	RbRenderer renderer = RbRenderer(maze, filename, marginPixels, cellPixels, mode, margR, margG, margB, anchor);
	renderer.buildAreaCodes(rb.areaCodes);
	renderer.startRender();
	cout << "Done rendering image file " << filename << ".\n";
}

void weaveStatic() {
	cout << "Let's get some information about how you want the Weaving Recursive Backtracker to generate and render your maze!\n\n";
	int startEdge;
	cout << "You can have the entrance for the maze placed randomly in one of five areas of the maze:\n\n";
	cout << "0 - Top Edge\n";
	cout << "1 - Right Edge\n";
	cout << "2 - Bottom Edge\n";
	cout << "3 - Left Edge\n";
	cout << "4 - Inside the Maze\n";
	cout << "Please enter the number corresponding to area you want the maze to start [then press Enter]: ";
	cin >> startEdge;
	system("cls");
	int endEdge;
	cout << "You can have the exit for the maze placed randomly in one of five areas of the maze:\n";
	cout << "0 - Top Edge\n";
	cout << "1 - Right Edge\n";
	cout << "2 - Bottom Edge\n";
	cout << "3 - Left Edge\n";
	cout << "4 - Inside the Maze\n";
	cout << "Please enter the number corresponding to area you want the maze to end [then press Enter]: ";
	cin >> endEdge;
	system("cls");
	float bias;
	cout << "'Bias' is when maze corridors tend to prefer either horizontal or vertical directions.\n";
	cout << "Whether there is a horizontal, vertical, or even bias affects the overall 'texture' of the maze.\n";
	cout << "To configure the bias, please enter a decimal or floating point number ranging from 0 to 1 inclusive.\n";
	cout << "If you want an 'even' bias, simply enter 0.5. For more horizontal bias, enter a number closer to 1.\n";
	cout << "For more vertical bias, enter a number closer to 0. Enter your bias [then press Enter]: ";
	cin >> bias;
	system("cls");
	cout << "To create interesting visual effects, you can ask the backtracker to randomly 'invert' the bias\n";
	cout << "that you just configured. If you would like the backtracker to randomly 'invert' the bias, enter 1.\n";
	cout << "If you don't want the backtracker to randomly 'invert' the bias, enter 0 [then press Enter]: ";
	int invertInput;
	cin >> invertInput;
	bool invert;
	if (invertInput == 1)
		invert = true;
	else
		invert = false;
	float inversionChance = 0.02f;
	if (invert) {
		int configureInput;
		bool configure = false;
		cout << "\nSince you chose to have the backtracker randomly invert the bias, you have an opportunity to\n";
		cout << "configure the actual chance that the backtracker has to randomly invert the bias during each\n";
		cout << "loop of the generation process. Warning: this is a finicky parameter for advanced usage only.\n";
		cout << "If you provide too high of a chance, the bias will invert too often, nullifying your earlier\n";
		cout << "bias preference that you provided. By default, the inversion chance is set to .02. Would you\n";
		cout << "like to manually configure the inversion chance? Enter 1 for yes, 0 for no [then press Enter]: ";
		cin >> configureInput;
		if (configureInput == 1)
			configure = true;
		if (configure) {
			cout << "Please provide a decimal or floating point value for the inversion chance between 0 and 1 exclusive [then press Enter]: ";
			cin >> inversionChance;
		}
	}
	system("cls");
	int loopsInput;
	bool loops = false;
	cout << "By default, a recursive backtracker maze does not have any loops. This means there is exactly one\n";
	cout << "path from anyone point in the maze to any other point. However, if you would like the maze to carve\n";
	cout << "a few loops at the end of the process for fun, enter 1. Otherwise, enter 0 [then press Enter]: ";
	cin >> loopsInput;
	if (loopsInput == 1)
		loops = true;
	system("cls");
	cout << "You need to decide how big you want your maze. Due to the admittedly opinionated graph model utilized\n";
	cout << "by the algorithm, you must specify both the width and height of your maze in odd numbers. It's okay\n";
	cout << "if you enter an even number, as in that case your preference will be truncated to the nearest odd number.\n";
	cout << "Also, for your first time, a suggested starting point is 101 wide and 101 high.\n";
	cout << "How many cells wide do you want your maze [then press Enter]: ";
	unsigned long long width;
	cin >> width;
	if (width < 1)
		width = 1uLL;
	if (width % 2 == 0)
		width -= 1;
	cout << "How many cells high do you want your maze [then press Enter]: ";
	unsigned long long height;
	cin >> height;
	if (height < 1)
		height = 1uLL;
	if (height % 2 == 0)
		height -= 1;
	system("cls");
	cout << "An image of your maze will be generated in PPM file format. This is an older, inefficient (space-wise)\n";
	cout << "file format, but it is used for convenience due to the difficulty of programmatically manipulating PNG and\n";
	cout << "JPG files. After your file is generated, your system's default image viewing application may not know what\n";
	cout << "to do with the image file. Rest assured, however, that it is easy to view and convert (i.e. to PNG, PDF, etc)\n";
	cout << "PPM image files in freely available image manipulation software such as LibreOffice Draw or GIMP.\n\n";
	cout << "You can now configure the dimension in pixels of your rendered maze image.\n";
	cout << "The suggested starting point (to avoid accidentally generating too large of an image) is 10 pixels for\n";
	cout << "the dimension for each cell in your maze and 10 pixels of margin space. In the case of cells in your maze,\n";
	cout << "a choice of '10' will indicate that every cell in your maze will be 10 pixels wide and 10 pixels tall.\n";
	cout << "In the case of margin, a choice of '10' will indicate a margin 10 pixels wide on all sides of your maze image.\n\n";
	int cellPixels;
	int marginPixels;
	cout << "How many pixels do you want for your maze cells (again, 10 is suggested for first-timers) [then press Enter]: ";
	cin >> cellPixels;
	cout << "How many pixels wide do you want the margin of your maze image to be [then press Enter]: ";
	cin >> marginPixels;
	system("cls");
	cout << "You can configure the colors in which your maze image is rendered by specifying standard RGB color values\n";
	cout << "ranging from 0 to 255. There are five different colors for you to configure: \n\n";
	int fillR, fillG, fillB, carveR, carveG, carveB, margR, margG, margB, startR, startG, startB, endR, endG, endB;
	cout << "Fill Color - for pixels in filled portions of maze (suggested RGB: 44,  82, 130 = dark blue)\n";
	cout << "Carve Color - for pixels in carved portions of maze (suggested RGB: 180, 210, 230 = light blue)\n";
	cout << "Start Color - for pixels in maze's starting cell (suggested RGB: 0, 210,   0 = green)\n";
	cout << "End Color - for pixels in maze's ending cell (suggested RGB: 210,   0,   0 = salmon)\n";
	cout << "Margin Color - for pixels in margin of maze image (suggested RGB: 255, 255, 255 = white)\n\n";
	cout << "You will now enter each of the three RGB color values one at a time separately for each of the\n";
	cout << "five colors. DO NOT enter more than one numeric value (e.g. for red and green) on the same line.\n\n";
	cout << "Red Fill Value [then press Enter]: ";
	cin >> fillR;
	cout << "Green Fill Value [then press Enter]: ";
	cin >> fillG;
	cout << "Blue Fill Value [then press Enter]: ";
	cin >> fillB;
	cout << "Red Carve Value [then press Enter]: ";
	cin >> carveR;
	cout << "Green Carve Value [then press Enter]: ";
	cin >> carveG;
	cout << "Blue Carve Value [then press Enter]: ";
	cin >> carveB;
	cout << "Red Start Value [then press Enter]: ";
	cin >> startR;
	cout << "Green Start Value [then press Enter]: ";
	cin >> startG;
	cout << "Blue Start Value [then press Enter]: ";
	cin >> startB;
	cout << "Red Exit Value [then press Enter]: ";
	cin >> endR;
	cout << "Green Exit Value [then press Enter]: ";
	cin >> endG;
	cout << "Blue Exit Value [then press Enter]: ";
	cin >> endB;
	cout << "Red Margin Value [then press Enter]: ";
	cin >> margR;
	cout << "Green Margin Value [then press Enter]: ";
	cin >> margG;
	cout << "Blue Margin Value [then press Enter]: ";
	cin >> margB;
	system("cls");
	cout << "Your maze will soon start generating.\n";
	cin.get();
	string filename;
	cout << "Please enter a filename (without an extension, as that will be added automatically) for your image [then press Enter]: ";
	getline(cin, filename);
	filename.append(".ppm");
	cout << "Press enter to confirm and start the maze generation process.\n";
	cin.get();
	Maze maze = Maze(width, height, 0x0000000000000000uLL);
	cout << "Generating...\n";
	WvRecursiveBacktracker rb = WvRecursiveBacktracker(maze, startEdge, endEdge, bias, invert, inversionChance, loops);
	cout << "Done generating maze. Starting image rendering process.\n";
	Renderer renderer = Renderer(maze, filename, marginPixels, cellPixels, fillR, fillG, fillB, carveR, carveG, carveB,
		startR, startG, startB, endR, endG, endB, margR, margG, margB);
	cout << "Done rendering image file " << filename << ".\n";
}

void weavePoly() {
	cout << "Let's get some information about how you want the Polychrome Weaving Recursive Backtracker to generate and render your maze!\n\n";
	int startEdge;
	cout << "You can have the entrance for the maze placed randomly in one of five areas of the maze:\n\n";
	cout << "0 - Top Edge\n";
	cout << "1 - Right Edge\n";
	cout << "2 - Bottom Edge\n";
	cout << "3 - Left Edge\n";
	cout << "4 - Inside the Maze\n\n";
	cout << "Please enter the number corresponding to area you want the maze to start [then press Enter]: ";
	cin >> startEdge;
	system("cls");
	int endEdge;
	cout << "You can have the exit for the maze placed randomly in one of five areas of the maze:\n\n";
	cout << "0 - Top Edge\n";
	cout << "1 - Right Edge\n";
	cout << "2 - Bottom Edge\n";
	cout << "3 - Left Edge\n";
	cout << "4 - Inside the Maze\n\n";
	cout << "Please enter the number corresponding to area you want the maze to end [then press Enter]: ";
	cin >> endEdge;
	system("cls");
	float bias;
	cout << "'Bias' is when maze corridors tend to prefer either horizontal or vertical directions.\n";
	cout << "Whether there is a horizontal, vertical, or even bias affects the overall 'texture' of the maze.\n";
	cout << "To configure the bias, please enter a decimal or floating point number ranging from 0 to 1 inclusive.\n";
	cout << "If you want an 'even' bias, simply enter 0.5. For more horizontal bias, enter a number closer to 1.\n";
	cout << "For more vertical bias, enter a number closer to 0. Enter your bias [then press Enter]: ";
	cin >> bias;
	system("cls");
	cout << "To create interesting visual effects, you can ask the backtracker to randomly 'invert' the bias\n";
	cout << "that you just configured. If you would like the backtracker to randomly 'invert' the bias, enter 1.\n";
	cout << "If you don't want the backtracker to randomly 'invert' the bias, enter 0 [then press Enter]: ";
	int invertInput;
	cin >> invertInput;
	bool invert;
	if (invertInput == 1)
		invert = true;
	else
		invert = false;
	float inversionChance = 0.02f;
	if (invert) {
		int configureInput;
		bool configure = false;
		cout << "\nSince you chose to have the backtracker randomly invert the bias, you have an opportunity to\n";
		cout << "configure the actual chance that the backtracker has to randomly invert the bias during each\n";
		cout << "loop of the generation process. Warning: this is a finicky parameter for advanced usage only.\n";
		cout << "If you provide too high of a chance, the bias will invert too often, nullifying your earlier\n";
		cout << "bias preference that you provided. By default, the inversion chance is set to .02. Would you\n";
		cout << "like to manually configure the inversion chance? Enter 1 for yes, 0 for no [then press Enter]: ";
		cin >> configureInput;
		if (configureInput == 1)
			configure = true;
		if (configure) {
			cout << "Please provide a decimal or floating point value for the inversion chance between 0 and 1 exclusive [then press Enter]: ";
			cin >> inversionChance;
		}
	}
	system("cls");
	int loopsInput;
	bool loops = false;
	cout << "By default, a recursive backtracker maze does not have any loops. This means there is exactly one\n";
	cout << "path from anyone point in the maze to any other point. However, if you would like the maze to carve\n";
	cout << "a few loops at the end of the process for fun, enter 1. Otherwise, enter 0 [then press Enter]: ";
	cin >> loopsInput;
	if (loopsInput == 1)
		loops = true;
	system("cls");
	cout << "You need to decide how big you want your maze. Due to the admittedly opinionated graph model utilized\n";
	cout << "by the algorithm, you must specify both the width and height of your maze in odd numbers. It's okay\n";
	cout << "if you enter an even number, as in that case your preference will be truncated to the nearest odd number.\n";
	cout << "Also, for your first time, a suggested starting point is 101 wide and 101 high.\n";
	cout << "How many cells wide do you want your maze [then press Enter]: ";
	unsigned long long width;
	cin >> width;
	if (width < 1)
		width = 1uLL;
	if (width % 2 == 0)
		width -= 1;
	cout << "How many cells high do you want your maze [then press Enter]: ";
	unsigned long long height;
	cin >> height;
	if (height < 1)
		height = 1uLL;
	if (height % 2 == 0)
		height -= 1;
	system("cls");
	cout << "An image of your maze will be generated in PPM file format. This is an older, inefficient (space-wise)\n";
	cout << "file format, but it is used for convenience due to the difficulty of programmatically manipulating PNG and\n";
	cout << "JPG files. After your file is generated, your system's default image viewing application may not know what\n";
	cout << "to do with the image file. Rest assured, however, that it is easy to view and convert (i.e. to PNG, PDF, etc)\n";
	cout << "PPM image files in freely available image manipulation software such as LibreOffice Draw or GIMP.\n\n";
	cout << "You can now configure the dimension in pixels of your rendered maze image.\n";
	cout << "The suggested starting point (to avoid accidentally generating too large of an image) is 10 pixels for\n";
	cout << "the dimension for each cell in your maze and 10 pixels of margin space. In the case of cells in your maze,\n";
	cout << "a choice of '10' will indicate that every cell in your maze will be 10 pixels wide and 10 pixels tall.\n";
	cout << "In the case of margin, a choice of '10' will indicate a margin 10 pixels wide on all sides of your maze image.\n\n";
	int cellPixels;
	int marginPixels;
	cout << "How many pixels do you want for your maze cells (again, 10 is suggested for first-timers) [then press Enter]: ";
	cin >> cellPixels;
	cout << "How many pixels wide do you want the margin of your maze image to be [then press Enter]: ";
	cin >> marginPixels;
	system("cls");
	cout << "This maze image renderer will dynamically pick the colors of your maze for you with a little configuration.\n";
	cout << "First, you need to specify the RGB color values (for the margin of your rendered maze image)\n";
	cout << "ranging from 0 to 255. Suggested RGB values: 255, 255, 255 = white\n\n";
	int margR, margG, margB;
	cout << "You will now enter each of the three RGB color values one at a time separately for the\n";
	cout << "margin color. DO NOT enter more than one numeric value (e.g. for red and green) on the same line.\n\n";
	cout << "Red Margin Value [then press Enter]: ";
	cin >> margR;
	cout << "Green Margin Value [then press Enter]: ";
	cin >> margG;
	cout << "Blue Margin Value [then press Enter]: ";
	cin >> margB;
	system("cls");
	int mode;
	cout << "There are four different polychrome rendering modes for you to choose from: \n\n";
	cout << "1 - static, light fill color and dark carve color are both randomly chosen.\n";
	cout << "2 - static, dark fill color and light carve color are both randomly chosen.\n";
	cout << "3 - dynamic, light fill color and dark carve color randomly chosen, randomly changed.\n";
	cout << "4 - dynamic, dark fill color and light carve color randomly chosen, randomly changed.\n\n";
	cout << "Please enter the number of the polychrome rendering mode you want [then press Enter]: ";
	cin >> mode;
	system("cls");
	int anchor = 0;
	float areaCodeIncChance = .005f;
	if (mode == 3 || mode == 4) {
		cout << "Since you chose a dynamic polychrome rendering mode, just a few more questions.\n\n";
		cout << "Please configure the chance you wish the generation process to have to change colors\n";
		cout << "during the rendering loop. The default chance is .005. This is a finicky parameter,\n";
		cout << "so it is advised for beginners to simply stick with that default value of .005.\n\n";
		cout << "Enter a decimal or floating point value between 0 and 1 exclusive [then press Enter]: ";
		cin >> areaCodeIncChance;
		cout << "\nYou must choose an 'anchoring' point for the background color gradient that the\n";
		cout << "renderer generates: \n\n";
		cout << "0 - Top Left Corner\n";
		cout << "1 - Top Edge\n";
		cout << "2 - Top Right Corner\n";
		cout << "3 - Right Edge\n";
		cout << "4 - Bottom Right Corner\n";
		cout << "5 - Bottom Edge\n";
		cout << "6 - Bottom Left Corner\n";
		cout << "7 - Left Edge\n";
		cout << "8 - Image Center\n\n";
		cout << "Please enter the number of the anchoring point you want [then press Enter]: ";
		cin >> anchor;
	}
	system("cls");
	cin.get();
	string filename;
	cout << "Please enter a filename (without an extension, as that will be added automatically) for your image [then press Enter]: ";
	getline(cin, filename);
	filename.append(".ppm");
	cout << "Press enter to confirm and start the maze generation process.\n";
	cin.get();
	Maze maze = Maze(width, height, 0x0000000000000000uLL);
	cout << "Generating...\n";
	RbWvRecursiveBacktracker rb = RbWvRecursiveBacktracker(maze, startEdge, endEdge, bias, invert, inversionChance, areaCodeIncChance, loops);
	cout << "Done generating maze. Starting image rendering process.\n";
	RbRenderer renderer = RbRenderer(maze, filename, marginPixels, cellPixels, mode, margR, margG, margB, anchor);
	renderer.buildAreaCodes(rb.areaCodes);
	renderer.startRender();
	cout << "Done rendering image file " << filename << ".\n";
}