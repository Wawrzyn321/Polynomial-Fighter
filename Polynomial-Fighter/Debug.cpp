#include <string>
#include "Debug.h"
#include "Timer.h"

void Debug::PrintFormatted(const std::string &format)
{
    std::cout << format;
}

void Debug::PrintErrorFormatted(const std::string &format)
{
	std::cout << format;
	Time::Timer *t = Time::Timer::instance();
	t->setTimeScale(0);
	system("pause");
}
