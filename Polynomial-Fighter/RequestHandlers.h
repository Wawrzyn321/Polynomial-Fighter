#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "Request.h"

class RequestHandler
{
protected:
	RequestHandler *succesor = nullptr;

	virtual bool canHandleRequest(const std::string &input) const = 0;

	virtual RequestValue handleImplementation(const std::string &input) const = 0;

	RequestValue passFurther(const std::string& input) const;
public:
	RequestHandler(RequestHandler* succesor);

	RequestValue handle(const std::string& input) const;

	virtual ~RequestHandler();
};

class EmptyStringHandler : public RequestHandler
{
public:
	EmptyStringHandler(RequestHandler *succesor) : RequestHandler(succesor) { }

protected:
	bool canHandleRequest(const std::string& input) const override;

	RequestValue handleImplementation(const std::string& input) const override;
};

class SingleNumberStringHandler : public RequestHandler
{
public:
	SingleNumberStringHandler(RequestHandler *succesor) : RequestHandler(succesor) { }

protected:
	bool canHandleRequest(const std::string& input) const override;

	RequestValue handleImplementation(const std::string& input) const override;
};

class LHSInequalityStringHandler : public RequestHandler
{
public:
	LHSInequalityStringHandler(RequestHandler *succesor) : RequestHandler(succesor) { }

protected:
	bool canHandleRequest(const std::string& input) const override;

	RequestValue handleImplementation(const std::string& input) const override;
};


class RHSInequalityStringHandler : public RequestHandler
{
public:
	RHSInequalityStringHandler(RequestHandler *succesor) : RequestHandler(succesor) { }

protected:
	bool canHandleRequest(const std::string& input) const override;

	RequestValue handleImplementation(const std::string& input) const override;
};


class ListStringHandler : public RequestHandler
{
public:
	ListStringHandler(RequestHandler *succesor) : RequestHandler(succesor) { }

protected:
	bool canHandleRequest(const std::string& input) const override;

	RequestValue handleImplementation(const std::string& input) const override;

private:
	static std::vector<std::string> tokenize(const std::string& input);
};


class DivisorStringHandler : public RequestHandler
{
public:
	DivisorStringHandler(RequestHandler *succesor) : RequestHandler(succesor) { }

protected:
	bool canHandleRequest(const std::string& input) const override;

	RequestValue handleImplementation(const std::string& input) const override;
};

#endif