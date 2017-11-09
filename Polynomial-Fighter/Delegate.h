#ifndef DELEGATE_H
#define DELEGATE_H
#include <functional>
#include <vector>

template <typename T>
class Delegate
{
	typedef std::function<void(T)> Function;
	std::vector<Function> content;
public:
	void add(Function fun)
	{
		content.push_back(fun);
	}

	void remove(Function fun)
	{
		content.erase(fun);
	}

	void clear()
	{
		content.clear();
	}

	void invoke(T param)
	{
		for (auto && f : content)
		{
			f(param);
		}
	}
};

#endif