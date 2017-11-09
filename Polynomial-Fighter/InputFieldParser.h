#ifndef INPUT_FIELD_PARSER_H
#define INPUT_FIELD_PARSER_H
#include "Request.h"

class InputFieldParser
{
public:
	static std::vector<int> parse(const std::string& input);

	static void runTests();
};


#endif