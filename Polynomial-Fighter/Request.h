#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <vector>
#include "Debug.h"

namespace RH_Codes
{
	const std::string NOT_A_NUMBER = "Not a number!";
	const std::string INVALID_INPUT = "Invalid input!";
	const std::string SUCCESOR_NULL = "Succesor is null!";
	const std::string OUT_OF_RANGE = "Out of range!";
	const std::string DIVISION_BY_ZERO = "Division by zero!";
	const std::string ROOTS = "Roots";
	const std::string DIVISOR = "Divisor";
	const std::string EMPTY = "Empty";
	//custom ones are also allowed
}

class Request
{
public:
	std::vector<int> result;
	std::string message;

	bool isValid() const
	{
		return message == RH_Codes::ROOTS
			|| message == RH_Codes::DIVISOR
			|| message == RH_Codes::EMPTY;
	}
};


#endif