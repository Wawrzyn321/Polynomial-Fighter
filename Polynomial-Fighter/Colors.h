#ifndef COLORS_H
#define COLORS_H
#include <SFML/Graphics/Color.hpp>

class Colors
{
	Colors(){}
	//https://color.adobe.com/pl/Copia-de-Copy-of-Sunset-Camping-color-theme-10363657/edit/?copy=true&base=2&rule=Complementary&selected=3&name=Kopia%20Copia%20de%20Copy%20of%20Sunset%20Camping&mode=rgb&rgbvalues=0.7233040036727432,0.807843137254902,0,0.699632992960467,0.77,0.09758355429785368,0.42081546038921486,0.47,0,0.5039571530355006,0.14735018122699423,0.77,0.26918064005909625,0,0.47&swatchOrder=0,1,2,3,4
public:
	static sf::Color FIRST;
	static sf::Color SECOND;
	static sf::Color THIRD;
	static sf::Color FOURTH;
	static sf::Color FIFTH;
	static sf::Color WHITE;
	static sf::Color BLACK;

	static sf::Color textLitColor;
	static sf::Color screenBackgroundColor;
	static sf::Color backgroundColor;
	static sf::Color outlineColor;
	static sf::Color textColor;

	static void load();
};

#endif