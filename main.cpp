/**
 * @file main.cpp
 * @author Michael Zalla
 * @date 9-28-2013
 *
 * Demonstrates the game-solving functionality of the Sudoku class.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "lib/Sudoku.h"
#include "utils/utils.h"

using namespace std;

int main(int argc, const char* argv[]) {

	string input_path;
	ifstream input_handle;
	string state;

	if(argc < 2) {
		cout << "Error: Missing input filename.\n\n";
		return EXIT_FAILURE;
	}

	//Store the path to the input file
	input_path = argv[1];

	//Parse the file's contents, storing the unsolved state in a single string
	//with all whitespace removed
	input_handle.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		//Default flag is 'ios::in' for ifstream
		input_handle.open(input_path.c_str());
		if(input_handle.is_open()) {
			//Assign the file's text contents to the string
			while(input_handle.good()) {
				string line;
				getline(input_handle, line);
				state += line;
			}
			input_handle.close();
		}
	} catch(const ifstream::failure e) {
		throw runtime_error("\nException occurred when opening or reading a file.\n");
	}

	state = Utilities::stripWhitespaces(state);

	Sudoku s(state);

	//Print the state that was initially provided
	s.printCurrentBoard();

	//Attempt to solve the game. If it is solvable, print the solution.
	//If the game is unsolvable, print a message to let the user know.
	if(s.solve()) {
		cout << "\nSolution found!\n";
		s.printCurrentBoard();
	} else {
		cout << "\nNo solution found!\n";
	}

	return EXIT_SUCCESS;

}
