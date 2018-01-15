#ifndef HELP_PROVIDER_h
#define HELP_PROVIDER_h

#include <string>
#include <vector>

namespace TextsProvider
{
	const std::vector<std::string> howTo = {
		"Your goal is to destroy\n     the polynomials.",
		"Find their roots!",
		" Type them into the form\n and press Enter to shoot.",
		"Use '<n' and '>n' to shoot\n     to multiple targets.",
		"Remember, bullets are\n       not infinite.",
		"Reduce the coefficients\n       by typing '/n'.",
		"The roots are between\n           -7 and 7.",
		"Press 'p' or Escape to\n     pause the game.",
		"Good luck.",
		//"Good luck, and don't\n forget not to divide by zero",
	};

	const std::vector<std::string> authors = {
		"         CEO\nBartek, Wawrzyn",
		" CTO\nBartek",
		"Chief visionary officer\n          Wawrzyn",
		"Quality Control Manager\n              Bartek",
		"Particle Master\n    Wawrzyn",
		"Chief creative officer\n         Wawrzyn",
		"Major Sound Artist\n       Wawrzyn",
		"Chief Evangelist\n     Wawrzyn",
		"Math Specialist\n       Bartek",
		"Chief gameplay creator\n          Wawrzyn",
		"Architecture Creator\n           Bartek",
		"Source Control Manager\n           Wawrzyn",
		"UI/UX Designer\n    Wawrzyn",
		"Copy-paste Executive\n         Wawrzyn",
		"   Chief testing officers\nHalamix2, Janczar, Noras",
		"Special thanks\n        Klux",
	};
}

#endif