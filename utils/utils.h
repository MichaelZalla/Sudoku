/** 
 * @file utils.h
 * @author Michael Zalla
 * @date 2013-10-05
 * @version 1.0.0
 *
 * Defines the public methods within the Utility class/wrapper. Each
 * of these methods become available to any class or source file that includes
 * this header.
 */

#ifndef UTILITIES_H
#define UTILITIES_H

//Protected includes (for argument and return types)
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <exception>

namespace Utilities {

	/*** Iterable methods ***/

	int sum(const std::vector<int>& v);

	/*** String manipulation functions ***/
	
	int stringToInt(const std::string& s);
	//string intToString(const int val);
	bool isAlphas(const std::string& s);
	bool isDigits(const std::string& s);
	std::string stripCharacters(const std::string& s, std::vector<char>& rm);
	std::string stripWhitespaces(const std::string& s);
	std::string ltrim(const std::string& s);
	std::string rtrim(const std::string& s);
	std::string trim(const std::string& s);
	std::string join(const std::vector<std::string>& strings);
	std::string join(const std::vector<std::string>& strings, const std::string delim_string = ", ");
	std::vector<std::string> split(const std::string& s, const char delim, std::vector<std::string>& elems);
	std::vector<std::string> split(const std::string& s, const char delim);
	
	/*** Text input functions ***/

	std::string getInput(const std::string& prompt);
	//Typedef for validator functions
	typedef bool (validatorFunction)(const std::string& response);
	std::string getValidInput(const std::string& prompt, validatorFunction& validate,
									 const std::string& errorMsg = "", bool onError = false);

};

namespace Exceptions {

	/*** Custom exception definitions ***/
	
	struct InvalidArgumentException : public std::exception {
		const char *what() const throw () {
			return "Attempt to invoke a function, class method, or class "
				   "constructor with one or more invalid argument values.";
		}
	};

}

#endif

