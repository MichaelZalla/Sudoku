/**
 * @file Sudoku.cpp
 * @author Michael Zalla
 * @date 9-27-2013
 *
 * Contains implementations for the public interface and private methods of the Sudoku
 * class. For details about this class, see 'Sudoku.h'.
 */

//Protected includes
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

//Header include
#include "Sudoku.h"

using namespace std;

//Initialize the const DIGITS vector
const int digits[ ] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const vector<int> Sudoku::DIGITS(digits, digits + 9);

/*** Public interface implementation ***/

Sudoku::Sudoku(const string& state_str) {
	//Parse the string to generate a vector of integers
	for(int i = 0; i < state_str.size(); i++) {
		char c = state_str[i];
		string s(1, c);
		//Unsolved values are denoted by a -1
		this->starting_board.push_back((c == '.') ? -1 : atoi(s.c_str()));
	}
	//Set the initial state of the current_board
	//this->current_board(this->starting_board);
	this->current_board = this->starting_board;
}

vector<int> Sudoku::getStartingBoard() const {
	return this->starting_board;
}

vector<int> Sudoku::getCurrentBoard() const {
	return this->current_board;
}

void Sudoku::printCurrentBoard() const {
	for(int row = 0; row < DIGITS.size(); row++) {
		//Print a horizontal divider if necessary
		if(row % 3 == 0) {
			cout << "+---+---+---+\n";
		}
		//Print the values of the row, separated into their associated squares
		for(int col = 0; col < DIGITS.size(); col++) {
			//Print a vertical divider if necessary
			if(col % 3 == 0) {
				cout << "|";
			}
			//Print the value, or indicate that it is yet to be solved for
			int val = this->current_board[getIndexByCoordinate(row, col)];
			if(val == -1 ) {
				cout << ".";
			} else {
				cout << val;
			}
		}
		cout << "|\n";
	}
	cout << "+---+---+---+\n";
}

int Sudoku::getIndexByCoordinate(int row, int col) {
	return (row * DIGITS.size()) + col;
}

vector<int> Sudoku::getIndicesOfRow(int row) {
	vector<int> ret;
	for(int i = 0; i < DIGITS.size(); i++) {
		ret.push_back(getIndexByCoordinate(row, i));
	}
	return ret;
}

vector<int> Sudoku::getIndicesOfCol(int col) {
	vector<int> ret;
	for(int i = 0; i < DIGITS.size(); i++) {
		ret.push_back(getIndexByCoordinate(i, col));
	}
	return ret;
}

vector<int> Sudoku::getIndicesOfSquare(int square) {
	vector<int> ret;
	const int SQUARE_SIZE = 3;
	int starting_row = (square / SQUARE_SIZE) * SQUARE_SIZE; //Integer division
	int starting_col = (square % SQUARE_SIZE) * SQUARE_SIZE;
	for(int row = 0; row < DIGITS.size(); row++) {
		for(int col = 0; col < DIGITS.size(); col++) {
			if(row >= starting_row && row < (starting_row + SQUARE_SIZE) &&
			   col >= starting_col && col < (starting_col + SQUARE_SIZE)) {
				ret.push_back(getIndexByCoordinate(row, col));
			}
		}
	}
	return ret;
}

/*** Private method implementations ***/

bool Sudoku::isValid() const {
	return isValid(this->getCurrentBoard());
}

bool Sudoku::isValid(const vector<int>& state) const {
	
	//Iterate through three sets of indices: the n-th row, the n-th column, and the
	//n-th square. Validate that no set contains duplicate values (more than one
	//instance of any digit). Allow for missing/unsolved values.

	//Iterate through each possible row/column/square index
	for(int i = 0; i < DIGITS.size(); i++) {

		vector<int> inNthRow = getIndicesOfRow(i);
		vector<int> inNthCol = getIndicesOfCol(i);
		vector<int> inNthSquare = getIndicesOfSquare(i);

		/*
		//Debugging - Print index sets
		cout << "\n";
		for(int i = 0; i < 9; i++) {
			cout.width(3);
			cout << inNthRow[i];
			cout.width(3);
			cout << inNthCol[i];
			cout.width(3);
			cout << inNthSquare[i];
			cout << "\n";
		}
		*/

		//Now, for each set of indices, validate its members
		vector<int> digitsForRow(DIGITS);
		vector<int> digitsForCol(DIGITS);
		vector<int> digitsForSquare(DIGITS);

		//Iterate through each value position for a set
		for(int j = 0; j < DIGITS.size(); j++) {
			int digits_index = 0;
			//Check current row value
			int row_val = state[inNthRow[j]];
			digits_index = find(digitsForRow.begin(), digitsForRow.end(), row_val) -
						   digitsForRow.begin();			
			//Check whether a matching value still exists within the digits vector
			if(digits_index < digitsForRow.size()) {
				//Remove the value from digitsForRow and continue
				digitsForRow.erase(digitsForRow.begin() + digits_index);
			} else {
				return false;
			}
			//Check current column value
			int col_val = state[inNthCol[j]];
			digits_index = find(digitsForCol.begin(), digitsForCol.end(), col_val) -
						   digitsForCol.begin();
			if(digits_index < digitsForCol.size()) {
				//Remove the value from digitsForCol and continue
				digitsForCol.erase(digitsForCol.begin() + digits_index);
			} else {
				return false;
			}
			//Check current square value
			int square_val = state[inNthSquare[j]];
			digits_index = find(digitsForSquare.begin(), digitsForSquare.end(), square_val) - 
						   digitsForSquare.begin();
			if(digits_index < digitsForSquare.size()) {
				//Remove the value from digitsForSquare and continue
				digitsForSquare.erase(digitsForSquare.begin() + digits_index);
			} else {
				return false;
			}
		}
	}

	return true;

}

bool Sudoku::isComplete() const {
	return isComplete(this->getCurrentBoard());
}

bool Sudoku::isComplete(const vector<int>& state) const {
	for(int i = 0; i < state.size(); i++) {
		if(state[i] == -1) return false;
	}
	return isValid(state);
}

