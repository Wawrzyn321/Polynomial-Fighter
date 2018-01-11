#include "Colors.h"
#include "Utility.h"
#include <fstream>
#include "GameData.h"

sf::Color Colors::FIRST;
sf::Color Colors::SECOND;
sf::Color Colors::THIRD;
sf::Color Colors::FOURTH;
sf::Color Colors::FIFTH;
sf::Color Colors::WHITE;
sf::Color Colors::BLACK;

sf::Color Colors::textLitColor;
sf::Color Colors::screenBackgroundColor;
sf::Color Colors::backgroundColor;
sf::Color Colors::outlineColor;
sf::Color Colors::textColor;

void Colors::load()
{
	std::fstream pIn = std::fstream(GameData::PATH_TO_RESOURCES + GameData::PATH_TO_COLOR_SCHEME);
	if (pIn.good())
	{
		int r, g, b;
		std::string temp;
		pIn >> r >> g >> b >> temp;
		FIRST = sf::Color(r, g, b);
		pIn >> r >> g >> b >> temp;
		SECOND = sf::Color(r, g, b);
		pIn >> r >> g >> b >> temp;
		THIRD = sf::Color(r, g, b);
		pIn >> r >> g >> b >> temp;
		FOURTH = sf::Color(r, g, b);
		pIn >> r >> g >> b >> temp;
		FIFTH = sf::Color(r, g, b);
		pIn >> r >> g >> b >> temp;
		WHITE = sf::Color(r, g, b);
		pIn >> r >> g >> b >> temp;
		BLACK = sf::Color(r, g, b);
	}
	else
	{
		FIRST = sf::Color(196, 206, 0);
		SECOND = sf::Color(188, 196, 25);
		THIRD = sf::Color(114, 120, 0);
		FOURTH = sf::Color(129, 38, 196);
		FIFTH = sf::Color(196, 206, 0);
		WHITE = sf::Color::White;
		BLACK = sf::Color::Black;
	}
	pIn.close();

	textLitColor = SECOND;
	screenBackgroundColor = lerp(FOURTH, BLACK, 0.9f);
	backgroundColor = lerp(FOURTH, BLACK, 0.8f);
	outlineColor = lerp(FIRST, BLACK, 0.1f);
	textColor = lerp(WHITE, THIRD, 0.2f);
}
