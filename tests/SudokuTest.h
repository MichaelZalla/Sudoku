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
		
		string state;

		state =  "123456789"
				 "456789123"
				 "789123456"
				 "234567891"
				 "567891234"
				 "891234567"
				 "345678912"
				 "678912345"
				 "912345678";

		Sudoku s(state);
		TS_ASSERT(s.isValid());
		
		state =  "223456789"
				 "456789123"
				 "789123456"
				 "234567891"
				 "567891234"
				 "891234567"
				 "345678912"
				 "678912345"
				 "912345678";

		Sudoku s2(state);
		TS_ASSERT(!s2.isValid());

		state =  "323456789"
				 "456789123"
				 "789123456"
				 "234567891"
				 "567891234"
				 "891234567"
				 "345678912"
				 "678912345"
				 "912345678";

		Sudoku s3(state);
		TS_ASSERT(!s3.isValid());

		state =  "123123123"
				 "123123123"
				 "123123123"
				 "456456456"
				 "456456456"
				 "456456456"
				 "789789789"
				 "789789789"
				 "789789789";
		
		Sudoku s4(state);
		TS_ASSERT(!s4.isValid());

	}

	void testIsComplete() {

		string state;

		state =  "123456789"
				 "456789123"
				 "789123456"
				 "234567891"
				 "567891234"
				 "891234567"
				 "345678912"
				 "678912345"
				 "912345678";

		Sudoku s(state);
		TS_ASSERT(s.isComplete());

		state = ".2345678."
				"4.67891.3"
				"78.123.56"
				"234.6.891"
				"5678.1234"
				"891.3.567"
				"34.678.12"
				"6.89123.5"
				".1234567.";

		Sudoku s2(state);
		TS_ASSERT(!s2.isComplete());

	}

	void testSolve() {

		string state = "123456789"
					   "456789123"
					   "789123456"
					   "234567891"
					   "567891234"
					   "891234567"
					   "345678912"
					   "678912345"
					   "912345678";

		Sudoku s(state);
		TS_ASSERT(s.solve());

		state = ".23456789"
				"4.6789123"
				"78.123456"
				"234.67891"
				"5678.1234"
				"89123.567"
				"345678.12"
				"6789123.5"
				"91234567.";

		Sudoku s2(state);
		TS_ASSERT(s2.solve());
		vector<int> solution = s2.getCurrentBoard();
		TS_ASSERT(solution[0] == 1 && solution[10] == 5 && solution[20] == 9);
		s2.printCurrentBoard();

		state = "1.657..9."
				"84..2.1.."
				".5.9.4..."
				"6.....2.3"
				".82.9.74."
				"4.7.....1"
				"...4.2.1."
				"..5.8..39"
				".7..598.4";

		Sudoku s3(state);
		TS_ASSERT(!s3.solve());

	}

};

#endif