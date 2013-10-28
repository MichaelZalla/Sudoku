/**
 * @file SudokuTest.h
 * @author Michael Zalla
 * @date 9-27-2013
 *
 * Contains unit tests for the Sudoku class.
 */

#ifndef SUDOKU_TEST_H
#define SUDOKU_TEST_H

//Protected includes
#include <string>
#include <iostream>
#include <vector>
#include <cxxtest/TestSuite.h>

//Header include
#include "../lib/Sudoku.h"

using namespace std;

class SudokuTest : public CxxTest::TestSuite {

public:

	void testConstructorWithSolvedState() {
		string state =  "123456789"
						"456789123"
						"789123456"
						"234567891"
						"567891234"
						"891234567"
						"345678912"
						"678912345"
						"912345678";
		Sudoku s(state);
		vector<int> starting_board = s.getStartingBoard();
		TS_ASSERT_EQUALS(starting_board[0], 1);
		TS_ASSERT_EQUALS(starting_board[80], 8);
	}

	void testConstructorWithUnsolvedState() {
		string state =  ".2345678."
						"4.67891.3"
						"78.123.56"
						"234.6.891"
						"5678.1234"
						"891.3.567"
						"34.678.12"
						"6.89123.5"
						".1234567.";
		Sudoku s(state);
		TS_ASSERT(true);
		vector<int> starting_board = s.getStartingBoard();
		TS_ASSERT_EQUALS(starting_board[0], -1);
		TS_ASSERT_EQUALS(starting_board[80], -1);
	}

	void testPrintCurrentBoard() {
		string state =  ".2345678."
						"4.67891.3"
						"78.123.56"
						"234.6.891"
						"5678.1234"
						"891.3.567"
						"34.678.12"
						"6.89123.5"
						".1234567.";
		Sudoku s(state);
		cout << "\n\n";
		s.printCurrentBoard();
		cout << "\n";
	}

	void testIsValid() {
		
		string state =  "123456789"
						"456789123"
						"789123456"
						"234567891"
						"567891234"
						"891234567"
						"345678912"
						"678912345"
						"912345678";
		
		string state2 =  "123123123"
						 "123123123"
						 "123123123"
						 "456456456"
						 "456456456"
						 "456456456"
						 "789789789"
						 "789789789"
						 "789789789";
		Sudoku s(state);
		Sudoku s2(state2);
		TS_ASSERT(s.isValid());
		TS_ASSERT(!s2.isValid());
	}

	void testIsComplete() {

		string state =  "123456789"
						"456789123"
						"789123456"
						"234567891"
						"567891234"
						"891234567"
						"345678912"
						"678912345"
						"912345678";
		
		string state2 =  ".2345678."
						 "4.67891.3"
						 "78.123.56"
						 "234.6.891"
						 "5678.1234"
						 "891.3.567"
						 "34.678.12"
						 "6.89123.5"
						 ".1234567.";

		Sudoku s(state);
		Sudoku s2(state2);
		TS_ASSERT(s.isComplete());
		TS_ASSERT(!s2.isComplete());
	}

};

#endif