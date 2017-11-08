#include "Request.h"

#include <sstream>
#include <iterator>
#include <algorithm>

Request RequestHandler::passFurther(const std::string& input) const
{
	if (succesor == nullptr)
	{
		return {{}, "Succesor is null!"};
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
	return find(input.begin(), input.end(), ' ') == input.end();
}

Request SingleNumberStringHandler::handleImplementation(const std::string& input) const
{
	try
	{
		int p = std::stoi(input);
		if (TEMPER::isInRangeInclusive(p))
		{
			return {{p}, ""};
		}
		else
		{
			return {{p}, "Out of range!"};
		}
	}
	catch (std::invalid_argument invalidArgumentException)
	{
		return passFurther(input);
	}
}

bool LHSInequalityStringHandler::canHandleRequest(const std::string& input) const
{
	return input.size() > 1 && (input[0] == '<' || input[0] == '>');
}

Request LHSInequalityStringHandler::handleImplementation(const std::string& input) const
{
	try
	{
		int p = std::stoi(input.substr(1));
		if (!TEMPER::isInRangeInclusive(p))
		{
			return {{p}, "Out of range!"};
		}

		if (input[0] == '<')
		{
			Request r;
			for (int i = -TEMPER::maxNumber; i < p; i++)
			{
				r.result.push_back(i);
			}
			return r;
		}
		else if (input[0] == '>')
		{
			Request r;
			for (int i = p + 1; i <= TEMPER::maxNumber; i++)
			{
				r.result.push_back(i);
			}
			return r;
		}
		else
		{
			return {{}, "Invalid character!"};
		}
	}
	catch (std::invalid_argument invalidArgumentException)
	{
		return passFurther(input);
	}
}

bool RHSInequalityStringHandler::canHandleRequest(const std::string& input) const
{
	return input.size() > 1 && (input.back() == '<' || input.back() == '>');
}

Request RHSInequalityStringHandler::handleImplementation(const std::string& input) const
{
	try
	{
		int p = std::stoi(input.substr(input.size() - 2));
		if (!TEMPER::isInRangeInclusive(p))
		{
			return {{p}, "Out of range!"};
		}

		if (input.back() == '<')
		{
			Request r;
			for (int i = p + 1; i <= TEMPER::maxNumber; i++)
			{
				r.result.push_back(i);
			}
			return r;
		}
		else if (input.back() == '>')
		{
			Request r;
			for (int i = -TEMPER::maxNumber; i < p; i++)
			{
				r.result.push_back(i);
			}
			return r;
		}
		else
		{
			return {{}, "Invalid character!"};
		}
	}
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
		std::vector<std::string> results = tokenize(input);
		
		for (auto&& result : results)
		{
			int p = stoi(result);
			if (TEMPER::isInRangeInclusive(p) && find(v.begin(), v.end(), p) == v.end())
			{
				v.push_back(p);
			}
			else {
				return { v, "Out of range!" };
			}
		}
		sort(v.begin(), v.end());
		return {v, ""};
	}
	catch (std::invalid_argument invalidArgumentException)
	{
		return {{}, "Invalid character @" + std::to_string(v.size() + 1) + "!"};
	}
}

std::vector<std::string> ListStringHandler::tokenize(const std::string& input)
{
	std::string unraw = input;
	std::istringstream iss(unraw);
	return std::vector<std::string>((std::istream_iterator<std::string>(iss)),
		std::istream_iterator<std::string>());
}

