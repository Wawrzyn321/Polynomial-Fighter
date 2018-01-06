#ifndef STRING_SUBPROCESSOR_H
#define STRING_SUBPROCESSOR_H

#include <string>

class RequestSubprocessor
{
public:
	static const int maxNumber = 7;

	static bool isInRangeInclusive(int r);

	static std::string removePeriods(std::string input);

	static std::string removeTrailingSpaces(const std::string& input);

	static bool hasSlash(const std::string& input);

	static bool hasInequalityCharacters(const std::string& input);

	static bool isNumber(const std::string& input);
};

#endif