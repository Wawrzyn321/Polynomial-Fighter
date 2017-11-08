#ifndef INPUT_FIELD_PARSER_H
#define INPUT_FIELD_PARSER_H
#include <vector>
#include "Request.h"
#include <iostream>

class InputFieldParser
{

	static std::string preprocess(const std::string& input)
	{
		std::string unraw = input;
		//remove ','
		for (unsigned i = 0; i < unraw.size(); i++)
		{
			if (unraw[i] == ',') unraw[i] = ' ';
		}
		return unraw;
	}

public:
	static std::vector<int> parse(const std::string &input)
	{
		std::string unraw = preprocess(input);
		RequestHandler *chain =
			new EmptyStringHandler(
				new SingleNumberStringHandler(
					new LHSInequalityStringHandler(
						new RHSInequalityStringHandler(
							new ListStringHandler(
								nullptr)))));
		Request r = chain->handle(unraw);
		if (r.isValid())
		{
			for (int result : r.result)
			{
				std::cout << result << " ";
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << r.message << std::endl;
		}
		std::cout << std::endl;
		delete chain;
		return r.result;
	}
};


#endif