#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <vector>

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


#endif