#ifndef INPUT_FIELD_PARSER_H
#define INPUT_FIELD_PARSER_H

#include <string>
#include "Request.h"

class InputFieldParser
{
public:
	static RequestValue parse(const std::string& input);

	static void runTests();
};


#endif