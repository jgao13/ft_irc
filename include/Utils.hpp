#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>
#include <cctype>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <fstream>


namespace ft 
{
	/* Prints the string text replacing every non-printable character into their ASCII hex code */
	void						print_f_all(std::string text);
	/* No effing clue what was that for */
	void 						error(std::string message, bool stop);
	/* Change every lowercase into uppercase character */
	std::string					strToUpper(std::string str_target);
	/* Splits a string using the delimiter and put the parts in a vector */
	std::vector<std::string> 	split(std::string str, std::string delimiter);
	/* Because C++98 */
	std::string					intToStr(int n);

	void						write_f_all(char * text);


}

#endif