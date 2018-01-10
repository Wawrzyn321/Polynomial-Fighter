#ifndef HELP_PROVIDER_h
#define HELP_PROVIDER_h

#include <string>

namespace HelpProvider
{
	const std::string texts[] = {
		"Your goal is to destroy\n    the polynomials.",
		"Find their roots!",
		"Type them into the form\n and press Enter to shoot.",
		"Use '<n' and '>n' to shoot\n   to multiple targets.",
		"Remember, bullets are\n           not infinite.",
		"Reduce the coefficients\n     by typing '/n'",
		"The roots are between\n       -7 and 7.",
		"Press 'p' or Escape to\n     pause the game.",
		"Good luck.",
	};
	const int len = 9;
}

#endif