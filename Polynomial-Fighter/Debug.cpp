#include <string>
#include "Debug.h"
#include "Timer.h"
#include "Utility.h"

using std::cout;
using std::endl;

void Debug::PrintFormatted(const std::string &format)
{
    cout << format;
}

void Debug::PrintErrorFormatted(const std::string &format)
{
    cout << format;
	Time::Timer *t = Time::Timer::instance();
	t->setTimeScale(0);
	system("pause");
}
