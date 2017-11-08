#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <vector>
class TEMPER
{
public:
	static const int maxNumber = 7;

	static bool isInRangeInclusive(int r)
	{
		return r >= -maxNumber && r <= maxNumber;
	}

};

class Request
{
public:
	std::vector<int> result;
	std::string message;

	bool isValid() const
	{
		return message.empty();
	}
};

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