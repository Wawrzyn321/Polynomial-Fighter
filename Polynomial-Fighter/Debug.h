#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <iostream>
#include "Utility.h"

class Debug {
public:

    template<typename T, typename... Args>
    static void PrintErrorFormatted(const char* text, T value, Args... RecArgs)
    {
        for (; *text != '\0'; text++) {
            if (*text == '%') {
                std::cout << toString(value);
                PrintFormatted(text + 1, RecArgs...);
                return;
            }
            std::cout << *text;
        }
    }

    static void PrintErrorFormatted(const char* format);

	template<typename T, typename... Args>
	static void PrintFormatted(const char* text, T value, Args... RecArgs)
	{
		for (; *text != '\0'; text++) {
			if (*text == '%') {
				std::cout << toString(value);
				PrintFormatted(text + 1, RecArgs...);
				return;
			}
			std::cout << *text;
		}
	}

    static void PrintFormatted(const char* format);
};

#endif

