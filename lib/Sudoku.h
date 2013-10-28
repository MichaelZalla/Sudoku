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

public:

	Sudoku(const string& state_str);
	vector<int> getStartingBoard() const;
	vector<int> getCurrentBoard() const;
	void printCurrentBoard() const;
	
	static const vector<int> DIGITS;
	static int getIndexByCoordinate(int row, int col);
	static vector<int> getIndicesOfRow(int row);
	static vector<int> getIndicesOfCol(int col);
	static vector<int> getIndicesOfSquare(int square);

	//Move these to private after testing
	bool isValid() const;
	bool isValid(const vector<int>& state) const;
	bool isComplete() const;
	bool isComplete(const vector<int>& state) const;

};

#endif