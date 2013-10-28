/**
 * @file Sudoku.h
 * @author Michael Zalla
 * @date 9-27-2013
 *
 * Describes the public interace and private methods of the Sudoku class. This class
 * is designed to take in an unsolved Sudoku puzzle and solve it recursively.
 */

#ifndef SUDOKU_H
#define SUDOKU_H

//Protected includes (for arguement and return types)
#include <string>
#include <vector>

using namespace std;

class Sudoku {

private:

	vector<int> starting_board;
	vector<int> current_board;
	//Private helped functions
	vector<int> getValuesByIndices(const vector<int>& state, const vector<int>& indices) const;
	//Private versions of Sudoku::isValid and Sudoku::isComplete
	bool isValid(const vector<int>& state) const;
	bool isComplete(const vector<int>& state) const;
	vector< vector<int> > getValidSuccessors(const vector<int>& state);
	bool solve(const vector<int>& state);

public:

	Sudoku(const string& state_str);
	//Public accessors
	vector<int> getStartingBoard() const;
	vector<int> getCurrentBoard() const;
	
	void printCurrentBoard() const;
	
	bool isValid() const;
	bool isComplete() const;
	bool solve();

	//Static class members and helper functions
	static const vector<int> DIGITS;
	static int getIndexByCoordinate(int row, int col);
	static vector<int> getIndicesOfRow(int row);
	static vector<int> getIndicesOfCol(int col);
	static vector<int> getIndicesOfSquare(int square);
	static bool containsDuplicateDigits(const vector<int>& ints);

};

#endif