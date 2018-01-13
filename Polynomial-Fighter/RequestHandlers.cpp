#include "RequestHandlers.h"
#include <sstream>
#include <algorithm>
#include "Debug.h"
#include "StringSubprocessor.h"

RequestValue RequestHandler::passFurther(const std::string& input) const
{
	if (succesor == nullptr)
	{
		return { {}, RH_Codes::SUCCESOR_NULL };
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

RequestValue RequestHandler::handle(const std::string& input) const
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
	delete succesor;
}


bool EmptyStringHandler::canHandleRequest(const std::string& input) const
{
	return input.empty();
}

RequestValue EmptyStringHandler::handleImplementation(const std::string& input) const
{
	return { {}, RH_Codes::EMPTY };
}


bool SingleNumberStringHandler::canHandleRequest(const std::string& input) const
{
	return !input.empty() &&
		!RequestSubprocessor::hasInequalityCharacters(input) &&
		!RequestSubprocessor::hasSlash(input) && 
		RequestSubprocessor::isNumber(input);
}

RequestValue SingleNumberStringHandler::handleImplementation(const std::string& input) const
{
	try
	{
		//check for incorrect characters
		if (!RequestSubprocessor::isNumber(input))
		{
			return { {}, RH_Codes::NOT_A_NUMBER };
		}
		int p = stoi(input);
		//check range
		if (RequestSubprocessor::isInRangeInclusive(p))
		{
			return { { p }, RH_Codes::ROOTS };
		}
		else
		{
			return { { p }, RH_Codes::OUT_OF_RANGE };
		}
	}
	//stoi error
	catch (std::invalid_argument &invalidArgumentException)
	{
		return passFurther(input);
	}
}


bool LHSInequalityStringHandler::canHandleRequest(const std::string& input) const
{
	//the characters after then inequality sign cannot be other inequality
	return input.size() > 1 && (input[0] == '<' || input[0] == '>') &&
		!RequestSubprocessor::hasSlash(input) &&
		!RequestSubprocessor::hasInequalityCharacters(input.substr(1));
}

RequestValue LHSInequalityStringHandler::handleImplementation(const std::string& input) const
{
	try
	{
		//check for incorrect characters
		if (!RequestSubprocessor::isNumber(input.substr(1)))
		{
			return { {}, RH_Codes::NOT_A_NUMBER };
		}
		int p = stoi(input.substr(1));
		//check range
		if (!RequestSubprocessor::isInRangeInclusive(p))
		{
			return { { p }, RH_Codes::OUT_OF_RANGE };
		}

		if (input[0] == '<')
		{
			//grab items <p
			std::vector<int> result;
			for (int i = -RequestSubprocessor::maxNumber; i < p; i++)
			{
				result.push_back(i);
			}
			return { result, RH_Codes::ROOTS };
		}
		//provided by canHandleRequest, there're no other cases than '>'
		else
		{
			//grab items >p
			std::vector<int> result;
			for (int i = p + 1; i <= RequestSubprocessor::maxNumber; i++)
			{
				result.push_back(i);
			}
			return { result, RH_Codes::ROOTS };
		}
	}
	//stoi error
	catch (std::invalid_argument &invalidArgumentException)
	{
		return passFurther(input);
	}
}


bool RHSInequalityStringHandler::canHandleRequest(const std::string& input) const
{
	//the characters before then inequality sign cannot be other inequality
	return input.size() > 1 && (input.back() == '<' || input.back() == '>') &&
		!RequestSubprocessor::hasSlash(input) &&
		!RequestSubprocessor::hasInequalityCharacters(input.substr(0, input.size() - 1));
}

RequestValue RHSInequalityStringHandler::handleImplementation(const std::string& input) const
{
	try
	{
		//check for incorrect characters
		if (!RequestSubprocessor::isNumber(input.substr(0, input.size() - 1)))
		{
			return { {}, RH_Codes::NOT_A_NUMBER };
		}
		int p = stoi(input.substr(0, input.size() - 1));
		//check range
		if (!RequestSubprocessor::isInRangeInclusive(p))
		{
			return { { p }, RH_Codes::OUT_OF_RANGE };
		}

		if (input.back() == '<')
		{
			//grab items >p
			std::vector<int> result;
			for (int i = p + 1; i <= RequestSubprocessor::maxNumber; i++)
			{
				result.push_back(i);
			}
			return { result, RH_Codes::ROOTS  };
		}
		else //provided by canHandleRequest, there're no other cases than '>'
		{
			//grab items <p
			std::vector<int> result;
			for (int i = -RequestSubprocessor::maxNumber; i < p; i++)
			{
				result.push_back(i);
			}
			return { result, RH_Codes::ROOTS };
		}
	}
	//stoi error
	catch (std::invalid_argument &invalidArgumentException)
	{
		return passFurther(input);
	}
}


bool ListStringHandler::canHandleRequest(const std::string& input) const
{
	return input.size() > 1 &&
		!RequestSubprocessor::hasSlash(input) &&
		!RequestSubprocessor::hasInequalityCharacters(input);
}

RequestValue ListStringHandler::handleImplementation(const std::string& input) const
{
	std::vector<int> v;
	try
	{
		//split input by spaces
		std::vector<std::string> results = tokenize(input);

		for (auto&& result : results)
		{
			//check for incorrect characters
			if (!RequestSubprocessor::isNumber(result))
			{
				return { { v }, "Not a number @" + std::to_string(v.size() + 1) + "!" };
			}
			int p = stoi(result);
			//check range
			if (RequestSubprocessor::isInRangeInclusive(p))
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
		return { v, RH_Codes::ROOTS };
	}
	//stoi error
	catch (std::invalid_argument &invalidArgumentException)
	{
		return { {}, "Invalid character @" + std::to_string(v.size() + 1) + "!" };
	}
}


bool DivisorStringHandler::canHandleRequest(const std::string& input) const
{
	return input.size() > 1 &&
		input[0] == '/' &&
		!RequestSubprocessor::hasInequalityCharacters(input);
}

RequestValue DivisorStringHandler::handleImplementation(const std::string& input) const
{
	try
	{
		std::string unraw = input.substr(1);
		//check for incorrect characters
		if (!RequestSubprocessor::isNumber(unraw))
		{
			return { {}, RH_Codes::NOT_A_NUMBER };
		}
		int p = stoi(unraw);
		//obvious division by zero
		if (p == 0)
		{
			return { { p }, RH_Codes::DIVISION_BY_ZERO };
		}
		//check range
		return { { p }, RH_Codes::DIVISOR };
	}
	//stoi error
	catch (std::invalid_argument &invalidArgumentException)
	{
		return passFurther(input);
	}
}
