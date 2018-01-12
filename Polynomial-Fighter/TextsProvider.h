#ifndef HELP_PROVIDER_h
#define HELP_PROVIDER_h

#include <string>
#include <vector>

namespace TextsProvider
{
	const std::vector<std::string> howTo = {
		"Your goal is to destroy\n    the polynomials.",
		"Find their roots!",
		"Type them into the form\n and press Enter to shoot.",
		"Use '<n' and '>n' to shoot\n   to multiple targets.",
		"Remember, bullets are\n           not infinite.",
		"Reduce the coefficients\n         by typing '/n'",
		"The roots are between\n              -7 and 7.",
		"Press 'p' or Escape to\n      pause the game.",
		"Good luck.",
		//"Good luck, and don't\n forget not to divide by zero",
	};

	const std::vector<std::string> authors = {
		"    CEO\nB.S., P.W.",
		"CTO\n B.S.",
		"Chief visionary officer\n                  P.W.",
		"Quality Control Manager\n                    B.S.",
		"Particle Master\n          P.W.",
		"Chief creative officer\n               P.W.",
		"Major Sound Artist\n              P.W.",
		"Chief Evangelist\n            P.W.",
		"Math Specialist\n            B.S.",
		"Chief gameplay creator\n                 P.W.",
		"Architecture Creator\n                 B.S.",
		"Source Control Manager\n                   P.W",
		"UI/UX Designer\n           P.W.",
		"Copy-paste Executive\n                 P.W.",
		"Chief testing officers\n   Halamix2, Janczar",
	};
}

#endif