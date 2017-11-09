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
	for (unsigned i = 0; i < input.size(); i++)
	{
		if (input[i] == ',') input[i] = ' ';
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
	return find(input.begin(), input.end(), '>') != input.end() ||
		find(input.begin(), input.end(), '<') != input.end();
}

bool RequestPreprocessor::isNumber(const std::string& input)
{
	removeTrailingSpaces(input);
	int i = 0;
	if (input[i] == '-')
	{
		i++;
	}
	for (; i < input.size(); i++)
	{
		if (input[i] < '0' || input[i] > '9')
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
