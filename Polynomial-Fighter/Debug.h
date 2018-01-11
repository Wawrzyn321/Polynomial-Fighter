#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <iostream>

class Debug {
public:

    template<typename T, typename... Args>
    static void PrintErrorFormatted(const char* text, T value, Args... RecArgs)
    {
        for (; *text != '\0'; text++) {
            if (*text == '%') {
                std::cout << std::to_string(value);
                PrintFormatted(text + 1, RecArgs...);
                return;
            }
            std::cout << *text;
        }
    }

    static void PrintErrorFormatted(const std::string &format);

	template<typename T, typename... Args>
	static void PrintFormatted(const char* text, T value, Args... RecArgs)
	{
		for (; *text != '\0'; text++) {
			if (*text == '%') {
				std::cout << value;
				PrintFormatted(text + 1, RecArgs...);
				return;
			}
			std::cout << *text;
		}
	}

    static void PrintFormatted(const std::string &format);
};

#endif

