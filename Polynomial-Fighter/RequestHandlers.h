#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "Request.h"

namespace RH_ErrorCodes
{
	const std::string NOT_A_NUMBER = "Not a number!";
	const std::string INVALID_INPUT = "Invalid input!";
	const std::string SUCCESOR_NULL = "Succesor is null!";
	const std::string OUT_OF_RANGE = "Out of range!";
	//custom ones are also allowed
}

class RequestHandler
{
protected:
	RequestHandler *succesor = nullptr;

	virtual bool canHandleRequest(const std::string &input) const = 0;

	virtual Request handleImplementation(const std::string &input) const = 0;

	Request passFurther(const std::string& input) const;
public:
	RequestHandler(RequestHandler* succesor);

	Request handle(const std::string& input) const;

	virtual ~RequestHandler();
};

class EmptyStringHandler : public RequestHandler
{
public:
	EmptyStringHandler(RequestHandler *succesor) : RequestHandler(succesor) { }

protected:
	bool canHandleRequest(const std::string& input) const override;

	Request handleImplementation(const std::string& input) const override;
};

class SingleNumberStringHandler : public RequestHandler
{
public:
	SingleNumberStringHandler(RequestHandler *succesor) : RequestHandler(succesor) { }

protected:
	bool canHandleRequest(const std::string& input) const override;

	Request handleImplementation(const std::string& input) const override;
};

class LHSInequalityStringHandler : public RequestHandler
{
public:
	LHSInequalityStringHandler(RequestHandler *succesor) : RequestHandler(succesor) { }

protected:
	bool canHandleRequest(const std::string& input) const override;

	Request handleImplementation(const std::string& input) const override;
};


class RHSInequalityStringHandler : public RequestHandler
{
public:
	RHSInequalityStringHandler(RequestHandler *succesor) : RequestHandler(succesor) { }

protected:
	bool canHandleRequest(const std::string& input) const override;

	Request handleImplementation(const std::string& input) const override;
};


class ListStringHandler : public RequestHandler
{
public:
	ListStringHandler(RequestHandler *succesor) : RequestHandler(succesor) { }

protected:
	bool canHandleRequest(const std::string& input) const override;

	Request handleImplementation(const std::string& input) const override;

private:
	static std::vector<std::string> tokenize(const std::string& input);
};


#endif