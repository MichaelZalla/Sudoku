/** 
 * @file utils.cpp
 * @author Michael Zalla
 * @date 2013-10-05
 * @version 1.0.0
 *
 * Defines the method implementations for the Utilities class/wrapper.
 * See utils.h for details about this class.
 */

//Protected includes
#include <exception>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>

//Header include
#include "utils.h"

using namespace std;

/*** Iterable functions ***/

int Utilities::sum(const std::vector<int>& v) {
	int sum = 0;
	for(std::vector<int>::const_iterator int_ptr = v.begin(); int_ptr != v.end(); ++int_ptr) {
		sum += *int_ptr;
	}
	return sum;	
}

/*** String manipulation functions ***/

/**
 * Safely casts a string to an integer, and returns the integer. Strings that
 * do not begin with an integer are cast to zero.
 *
 * @param 	&s 	A const reference to the string holding an integer-like value
 */
int Utilities::stringToInt(const string &s) {
	return atoi(s.c_str());
}

/**
 * Returns a boolean value indicating whether or not the  given string contains
 * only digit characters (0,1,2,3,4,5,6,7,8,9).
 *
 * @param 	&s 	A const reference to the string to be tested
 */
bool Utilities::isDigits(const string &s) {
	bool ret = true;
	for(size_t i = 0; i < s.size(); i++) {
		if(!isdigit(s[i])) {
			ret = false;
		}
	}
	return ret;
}

/**
 * Returns a boolean value indicating whether or not the  given string contains
 * only alphabetical characters (A, B, C, a, b, c, etc).
 *
 * @param 	&s 	A const reference to the string to be tested
 */
bool Utilities::isAlphas(const std::string &s) {
	bool ret = true;
	for(size_t i = 0; i < s.size(); i++) {
		if(!isalpha(s[i])) {
			ret = false;
		}
	}
	return ret;
}

/**
 * Returns a new string in which all characters matching any of the elements
 * contained within the given rm[] array have been removed.
 *
 * @param 	&s 		A const reference to the original string
 * @param 	&rm 	A reference to a vector of characters to be removed
 */
string Utilities::stripCharacters(const string &s, vector<char> &rm) {
	//Get the value of the original referenced string
	string ret = s;
	for(size_t i = 0; i < rm.size(); i++) {
		char c = rm[i];
		ret.erase(
			//Transforms the range [first,last) into a range with all the elements
			//that compare equal to 'c' removed, and returns an iterator to the new
			//end of that range.
			remove(ret.begin(), ret.end(), c),
			ret.end()
		);
	}
	return ret;
}

/**
 * Similar to Utilities::stripCharacters. Returns a new string in which all whitespace
 * characters have been sequentially removed. Includes single spaces, tabs, newlines,
 * and carriage returns.
 *
 * @param 	&s 	A const reference to the original string
 */
string Utilities::stripWhitespaces(const string &s) {
	//Get the value of the original referenced string
	string ret = s;
	//Define a list of all whitespace character values
	//const char ws_chars[] = {' ', '\t', '\n', '\v', '\f', '\r'};
	char ws_chars[] = " \t\n\v\f\r";
	//Iterate over the list, remove any instances of the current char from the string
	for(int i = 0; i < strlen(ws_chars); i++) {
		char c = ws_chars[i];
		ret.erase(
			//Transforms the range [first,last) into a range with all the elements
			//that compare equal to 'c' removed, and returns an iterator to the new
			//end of that range.
			remove(ret.begin(), ret.end(), c),
			ret.end()
		);
	}
	return ret;
}

/**
 * Accepts a constant reference to an original string and returns a new string
 * in which any leading whitespace characters have been removed.
 *
 * @param 	&s 	A const reference to the original string
 */
string Utilities::ltrim(const string &s) {
	//Get the value of the original referenced string
	string ret = s;
	ret.erase(
		ret.begin(),
		find_if(
			ret.begin(),
			ret.end(),
			not1(ptr_fun<int, int>(isspace))
		)
	);
	return ret;
}

/**
 * Accepts a constant reference to an original string and returns a new string
 * in which any ending whitespace characters have been removed.
 *
 * @param 	&s 	A const reference to the original string
 */
string Utilities::rtrim(const string &s) {
	//Get the value of the original referenced string
	string ret = s;	
	ret.erase(
		find_if(
			ret.rbegin(),
			ret.rend(),
			not1(ptr_fun<int, int>(isspace))
		).base(),
		ret.end()
	);
	return ret;
}

/**
 * Accepts a constant reference to an original string and returns a new string
 * in which any leading and ending whitespace characters have been removed.
 *
 * @param 	&s 	A const reference to the original string
 */
string Utilities::trim(const string &s) {
	string ret = ltrim(s);
	ret = rtrim(ret);
	return ret;
}

/**
 * Accepts references to a string, a delimeter character, and a vector container. Splits
 * each section of the string bounded by the delimeter and pushes each section (word,
 * sentence, etc) into the vector container, which is returned by the function.
 * 
 * @param	&s  		A const reference to the string to be split
 * @param	&delim 		A const reference to a single delimeter character
 * @param	&elems  	A reference to a vector container in which to place the string sections
 */
vector<string> Utilities::split(const string &s, const char delim, vector<string> &elems) {
    //Create a new stringstream, passing the original string into its constructor
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

/**
 * A simpler implementation of Utilities::split that generates its own string vector
 * container which is populated with the sections of the string.
 *
 * @param	&s  		A const reference to the string to be split
 * @param	&delim 		A const reference to a single delimeter character
 */
vector<string> Utilities::split(const string &s, const char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

/**
 * Accepts a reference to a string vector, and returns a new string in which all
 * elements within the vector have been concatenated. No additional characters are
 * added between elements.
 *
 * @param 	&strings 	A const reference to a string vector
 */
string Utilities::join(const vector<string> &strings) {
	string ret = "";
	for(size_t i = 0; i < strings.size(); i++) {
		ret.append(strings[i]);
	}
	return ret;
}

/**
 * Accepts a reference to a string vector, and returns a new string in which all
 * elements within the vector have been concatenated. No additional characters are
 * added between elements. Note that the C++ compiler allows default values to be
 * given to constant references, but not to non-constant references.
 *
 * @param 	&strings 		A const reference to a string vector
 * @param 	delim_string 	A string to place between each element of &strings
 */
string Utilities::join(const vector<string> &strings, const string delim_string) {
	string ret = "";
	for(size_t i = 0; i < strings.size(); i++) {
		if(i != 0) {
			//For documentation on the std::string::append prototype, see:
			//http://www.cplusplus.com/reference/string/string/append/
			ret.append(delim_string);
		}
		ret.append(strings[i]);
	}
	return ret;
}

/*** Text input functions ***/

/**
* Used to collect command-line input from a program user.
*
* @param	&prompt		A const reference to a string prompting the user to enter a specific value
*/
string Utilities::getInput(const string &prompt) {
	//Initialize an empty string literal, as opposed to a single character
	string input;
	cout << prompt << endl;
	cin >> input;
	return input;
}

/**
 * Prompts the user for a specified input and validates the input using a given validator
 * function provided as an argument. This validator function's structure is defined by
 * the validatorFunction type, which takes a single response string and returns a boolean
 * value indicating whether the given input is valid. This function will continually
 * prompt the user until valid input is provided, at which point this input is returned.
 * 
 * @param	&prompt 	A const reference to a string prompting the user for a specific value
 * @param	&validate 	A reference to a function whose role it is to determine whether the
 * 						input is valid
 * @param	&errorMsg 	A const reference to an error message to be displayed when the user
 *						enters invalid input
 * @param 	onError 	An optional boolean value used by the function for subsequent
 *						(recursive) calls
 */
string Utilities::getValidInput(const string& prompt,
						validatorFunction& validate,
					 	const string& errorMsg,
					 	bool onError) {
	
	//Give the error message a default value
	string msg = ((errorMsg != "") ? errorMsg : "Error: Invalid input. Please enter a valid input.");

	string response,
		   request = ((!onError) ? (prompt + "\n") : (msg + "\n")); 
	
	//Request the user's input (all characters before the first line return)
	cout << request;
	
	//Clear the standard input buffer to ignore previous inputs
	//(which could trigger an error message)
	cin.clear();
	cin.ignore();

	getline(cin, response);
	
	while(1) {		
		if(validate(response)) {
			return response;
		} else {
			return getValidInput(prompt, validate, msg, true);
		}
	}
}

