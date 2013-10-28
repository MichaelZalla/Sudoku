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

/**
 * Public constructor. Takes a reference to a string describing a possible unsolved Sudoku
 * game, translates this string into a vector of puzzle values, and initializes the object's
 * starting_board and current_board members.
 *
 * @param 	state 	A reference to a Sudoku game string
 */
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

//Public getter for the starting_board member
vector<int> Sudoku::getStartingBoard() const {
	return this->starting_board;
}

//Public getter for the current_board member
vector<int> Sudoku::getCurrentBoard() const {
	return this->current_board;
}

/**
 * Prints the current board configuration to standard output, dividing each set
 * of nine digits into their own respective squares.
 */
void Sudoku::printCurrentBoard() const {
	cout << "\n";
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

//Public form of the isValid method; calls the private form, passing it the current state
bool Sudoku::isValid() const {
	return isValid(this->getCurrentBoard());
}

//Public form of the isComplete method; calls the private form, passing it the current state
bool Sudoku::isComplete() const {
	return isComplete(this->getCurrentBoard());
}

//Public form of the solve method
bool Sudoku::solve() {
	//Shouldn't this modify the current_board member if the game is solved?
	return solve(this->getCurrentBoard());
}

/*** Static class method implementations ***/

/**
 * Returns the index of a single board item specified by its row and column indices.
 *
 * @param 	row 	The index of the desired row
 * @param 	col 	The index of the desired column
 */
int Sudoku::getIndexByCoordinate(int row, int col) {
	return (row * DIGITS.size()) + col;
}

/**
 * Returns a vector containing the index of every board item that exists in the
 * specified row. These values are unchanging across different board states.
 *
 * @param 	row 	The index of the target row
 */
vector<int> Sudoku::getIndicesOfRow(int row) {
	vector<int> ret;
	for(int i = 0; i < DIGITS.size(); i++) {
		ret.push_back(getIndexByCoordinate(row, i));
	}
	return ret;
}

/**
 * Returns a vector containing the index of every board item that exists in the
 * specified column. These values are unchanging across different board states.
 *
 * @param 	col 	The index of the desired column
 */
vector<int> Sudoku::getIndicesOfCol(int col) {
	vector<int> ret;
	for(int i = 0; i < DIGITS.size(); i++) {
		ret.push_back(getIndexByCoordinate(i, col));
	}
	return ret;
}

/**
 * Returns a vector containing the index of every board item that exists in the
 * specified 'square'. These values are unchanging across different board states.
 *
 * @param 	square 	The index of the desired square (ordered left-to-right, top-to-bottom)
 */
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

/**
 * Returns a boolean value indicating whether a vector of integers contains
 * any duplicates. Consequently, it also tests whether the given vector contains
 * any non-digit values.
 * 
 * @param 	ints 	An integer vector of arbitrary length
 */
bool Sudoku::containsDuplicateDigits(const vector<int>& ints) {
	vector<int> digits(DIGITS);
	for(int i = 0; i < ints.size(); i++) {
		int value = ints[i];
		if(value != -1) {
			//Check whether a matching value still exists within the 'digits' vector
			int digits_index = find(digits.begin(), digits.end(), value) - digits.begin();
			if(digits_index < digits.size()) {
				//Remove the value from 'digits' and continue
				digits.erase(digits.begin() + digits_index);
			} else {
				//We've hit a duplicate
				return true;
			}
		}
	}
	return false;
}

/*** Private method implementations ***/

/**
 * Accepts a vector of indices and returns a vector in which each index has
 * been mapped to its associated value in a given state.
 *
 * @param 	state 		A reference to a vector describing a possible game state
 * @param 	indices 	A list of item indices associated with the game state
 */
vector<int> Sudoku::getValuesByIndices(const vector<int>& state, const vector<int>& indices) const {
	vector<int> ret;
	for(int i = 0; i < indices.size(); i++) {
		int value = state[indices[i]];
		ret.push_back(value);
	}
	return ret;
}

/**
 * Returns a boolean value indicating whether a given game state has a valid configuration.
 * The method makes nine iterations; within each iteration, it determines three value sets -
 * one for the n-th row, one for the n-th column, and one for the n-th square - and tests
 * whether or not any of these value sets contain duplicate digit values (not including a
 * value of negative one, allowing for missing or unsolved values).
 *
 * @param 	state 	A reference to a vector describing a possible game state
 */
bool Sudoku::isValid(const vector<int>& state) const {
	//Iterate through each possible row-column-square index
	for(int i = 0; i < DIGITS.size(); i++) {
		vector<int> row_values = getValuesByIndices(state, getIndicesOfRow(i));
		vector<int> col_values = getValuesByIndices(state, getIndicesOfCol(i));
		vector<int> square_values = getValuesByIndices(state, getIndicesOfSquare(i));
		/*
		//Debugging
		cout << "\nContains duplicate digits in row " << i << ": " << containsDuplicateDigits(row_values) << "\n";
		cout << "\nContains duplicate digits in col " << i << ": " << containsDuplicateDigits(col_values) << "\n";
		cout << "\nContains duplicate digits in square " << i << ": " << containsDuplicateDigits(square_values) << "\n";
		*/
		if(containsDuplicateDigits(row_values) ||
		   containsDuplicateDigits(col_values) || 
		   containsDuplicateDigits(square_values)) {
			return false;
		}
	}
	return true;
}

/**
 * Returns a boolean value indicating whether a given game state has both
 * a valid contiguration and contains no missing values.
 */
bool Sudoku::isComplete(const vector<int>& state) const {
	for(int i = 0; i < state.size(); i++) {
		if(state[i] == -1) return false;
	}
	return isValid(state);
}

vector< vector<int> > Sudoku::getValidSuccessors(const vector<int>& state) {
	vector< vector<int> > ret;
	//Determine the index of the next missing value
	int first_missing_index;
	for(int item_index = 0; item_index < state.size(); item_index++) {
		if(state[item_index] == -1) {
			first_missing_index = item_index;
			break;
		}
	}
	//Iterate through each possible digit value
	for(int digits_index = 0; digits_index < DIGITS.size(); digits_index++) {
		//Create a temporary board state using the current digit, and test the state's validity
		vector<int> temp = state;	
		temp[first_missing_index] = DIGITS[digits_index];
		if(isValid(temp)) {
			//cout << "Solved for value " << temp[first_missing_index] << " at index " << first_missing_index << "\n";
			//cout << "Adding new potential stat e to ret\n";
			ret.push_back(temp);
		}
	}
	return ret;
}

/**
 * A recursive approach to solving incomplete Sudoku games. Returns a boolean value
 * indicating whether the provided state could be solved (assigning the current_board
 * member to the resulting solved state must be accomplished as a side-effect).
 *
 * @param 	state 	A reference to a vector describing a possible game state
 */
bool Sudoku::solve(const vector<int>& state) {
	vector<int> board = state;
	//Test whether the board that was passed in is complete (exit condition)
	if(isComplete(board)) {
		//Class member assignment as side-effect
		this->current_board = board;
		return true;
	} else {
		//Recursive solving algorithm: Generate a list of all 'next moves' which are
		//valid, calling solve() recursively on each
		vector< vector<int> >successors = getValidSuccessors(board);
		for(int i = 0; i < successors.size(); i++) {
			if(solve(successors[i])) {
				return true;
			}
		}
		//We've hit a potential dead-end, so return false to end any more recursion
		//down the current rabbit-hole
		return false;
	}
}

