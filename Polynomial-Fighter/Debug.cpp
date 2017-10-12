#include "Debug.h"
#include "Timer.h"
#include "Utility.h"

using std::cout;
using std::endl;
void Debug::PrintFormatted(const char* format) {
    cout << toString(format);
}

void Debug::PrintErrorFormatted(const char* format) {
    cout << toString(format);
	Time::Timer *t = Time::Timer::instance();
	t->setTimeScale(0);
	system("pause");
}
