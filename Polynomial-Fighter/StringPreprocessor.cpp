#include "StringPreprocessor.h"
#include "RequestHandlers.h"
#include <iterator>
#include <sstream>

bool RequestPreprocessor::isInRangeInclusive(int r)
{
	return r >= -maxNumber && r <= maxNumber;
}

std::string RequestPreprocessor::removePeriods(std::string input)
{
	for (char &i : input)
	{
		if (i == ',') i = ' ';
	}
	return input;
}

std::string RequestPreprocessor::removeTrailingSpaces(const std::string& input)
{
	unsigned start = 0;
	while (start < input.size() && input[start] == ' ') start++;
	unsigned end = static_cast<int>(input.size()) - 1;
	while (end > start && input[end] == ' ') end--;
	return input.substr(start, end - start + 1);
}

bool RequestPreprocessor::hasInequalityCharacters(const std::string& input)
{
	return input.find('>') != std::string::npos ||
		input.find('<') != std::string::npos;
}

bool RequestPreprocessor::isNumber(const std::string& input)
{
	std::string unraw = removeTrailingSpaces(input);
	int i = 0;
	if (unraw[i] == '-')
	{
		i++;
	}
	for (; i < unraw.size(); i++)
	{
		if (unraw[i] < '0' || unraw[i] > '9')
		{
			return false;
		}
	}
	return true;
}

std::vector<std::string> ListStringHandler::tokenize(const std::string& input)
{
	std::istringstream iss(input);
	return std::vector<std::string>(
		std::istream_iterator<std::string>(iss),
		std::istream_iterator<std::string>());
}
