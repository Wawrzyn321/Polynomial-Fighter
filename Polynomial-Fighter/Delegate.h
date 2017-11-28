#ifndef DELEGATE_H
#define DELEGATE_H
#include <functional>
#include <vector>

class Action
{
	typedef std::function<void()> Function0;
	std::vector<Function0> content;
public:
	void add(Function0 fun)
	{
		content.push_back(fun);
	}

	void remove(Function0 fun)
	{
		//content.erase(fun);
	}

	void clear()
	{
		content.clear();
	}

	void invoke()
	{
		for (auto && f : content)
		{
			f();
		}
	}

	void operator()()
	{
		invoke();
	}
};

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

	void operator()(T param)
	{
		invoke(param);
	}
};


#endif