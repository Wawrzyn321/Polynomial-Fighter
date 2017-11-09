#include "RequestHandlers.h"
#include "StringPreprocessor.h"
#include <sstream>
#include <iterator>
#include <algorithm>

Request RequestHandler::passFurther(const std::string& input) const
{
	if (succesor == nullptr)
	{
		return { {}, RH_ErrorCodes::SUCCESOR_NULL };
	}
	else
	{
		return succesor->handle(input);
	}
}

RequestHandler::RequestHandler(RequestHandler* succesor)
{
	this->succesor = succesor;
}

Request RequestHandler::handle(const std::string& input) const
{
	if (canHandleRequest(input))
	{
		return handleImplementation(input);
	}
	else
	{
		return passFurther(input);
	}
}

RequestHandler::~RequestHandler()
{
	if (succesor)
	{
		delete succesor;
	}
}


bool EmptyStringHandler::canHandleRequest(const std::string& input) const
{
	return input.size() == 0;
}

Request EmptyStringHandler::handleImplementation(const std::string& input) const
{
	return {};
}


bool SingleNumberStringHandler::canHandleRequest(const std::string& input) const
{
	return RequestPreprocessor::isNumber(input);
}

Request SingleNumberStringHandler::handleImplementation(const std::string& input) const
{
	try
	{
		//check for incorrect characters
		if (!RequestPreprocessor::isNumber(input))
		{
			return { {}, RH_ErrorCodes::NOT_A_NUMBER };
		}
		int p = stoi(input);
		//check range
		if (RequestPreprocessor::isInRangeInclusive(p))
		{
			return { { p }, "" };
		}
		else
		{
			return { { p }, RH_ErrorCodes::OUT_OF_RANGE };
		}
	}
	//stoi error
	catch (std::invalid_argument invalidArgumentException)
	{
		return passFurther(input);
	}
}


bool LHSInequalityStringHandler::canHandleRequest(const std::string& input) const
{
	//the characters after then inequality sign cannot be other inequality
	return input.size() > 1 && (input[0] == '<' || input[0] == '>') && 
		!RequestPreprocessor::hasInequalityCharacters(input.substr(1));
}

Request LHSInequalityStringHandler::handleImplementation(const std::string& input) const
{
	try
	{
		//check for incorrect characters
		if (!RequestPreprocessor::isNumber(input.substr(1)))
		{
			return { {}, RH_ErrorCodes::NOT_A_NUMBER };
		}
		int p = stoi(input.substr(1));
		//check range
		if (!RequestPreprocessor::isInRangeInclusive(p))
		{
			return { { p }, RH_ErrorCodes::OUT_OF_RANGE };
		}

		if (input[0] == '<')
		{
			//grab items <p
			std::vector<int> result;
			for (int i = -RequestPreprocessor::maxNumber; i < p; i++)
			{
				result.push_back(i);
			}
			return { result, "" };
		}
		//provided by canHandleRequest, there're no other cases than '>'
		else
		{
			//grab items >p
			std::vector<int> result;
			for (int i = p + 1; i <= RequestPreprocessor::maxNumber; i++)
			{
				result.push_back(i);
			}
			return { result, "" };
		}
	}
	//stoi error
	catch (std::invalid_argument invalidArgumentException)
	{
		return passFurther(input);
	}
}


bool RHSInequalityStringHandler::canHandleRequest(const std::string& input) const
{
	//the characters before then inequality sign cannot be other inequality
	return input.size() > 1 && (input.back() == '<' || input.back() == '>') &&
		!RequestPreprocessor::hasInequalityCharacters(input.substr(0, input.size() - 1));
}

Request RHSInequalityStringHandler::handleImplementation(const std::string& input) const
{
	try
	{
		//check for incorrect characters
		if (!RequestPreprocessor::isNumber(input.substr(0, input.size() - 1)))
		{
			return { {}, RH_ErrorCodes::NOT_A_NUMBER };
		}
		int p = stoi(input.substr(0, input.size() - 1));
		//check range
		if (!RequestPreprocessor::isInRangeInclusive(p))
		{
			return { { p }, RH_ErrorCodes::OUT_OF_RANGE };
		}

		if (input.back() == '<')
		{
			//grab items >p
			std::vector<int> result;
			for (int i = p + 1; i <= RequestPreprocessor::maxNumber; i++)
			{
				result.push_back(i);
			}
			return {result, ""};
		}
		else //provided by canHandleRequest, there're no other cases than '>'
		{
			//grab items <p
			std::vector<int> result;
			for (int i = -RequestPreprocessor::maxNumber; i < p; i++)
			{
				result.push_back(i);
			}
			return { result, "" };
		}
	}
	//stoi error
	catch (std::invalid_argument invalidArgumentException)
	{
		return passFurther(input);
	}
}


bool ListStringHandler::canHandleRequest(const std::string& input) const
{
	return true;
}

Request ListStringHandler::handleImplementation(const std::string& input) const
{
	std::vector<int> v;
	try
	{
		//split input by spaces
		std::vector<std::string> results = tokenize(input);

		for (auto&& result : results)
		{
			//check for incorrect characters
			if (!RequestPreprocessor::isNumber(result))
			{
				return { { v }, "Not a number @" + std::to_string(v.size() + 1) + "!" };
			}
			int p = stoi(result);
			//check range
			if (RequestPreprocessor::isInRangeInclusive(p))
			{
				//no duplicates!
				if (find(v.begin(), v.end(), p) == v.end()) {
					v.push_back(p);
				}
			}
			else {
				return { v, "Out of range @" + std::to_string(v.size() + 1) + "!" };
			}
		}
		sort(v.begin(), v.end());
		return { v, "" };
	}
	//stoi error
	catch (std::invalid_argument invalidArgumentException)
	{
		return { {}, "Invalid character @" + std::to_string(v.size() + 1) + "!" };
	}
}
