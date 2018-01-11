#ifndef COLORS_H
#define COLORS_H
#include <SFML/Graphics/Color.hpp>
#include <fstream>
#include "GameData.h"

class Colors
{
	Colors(){}
	//https://color.adobe.com/pl/Copia-de-Copy-of-Sunset-Camping-color-theme-10363657/edit/?copy=true&base=2&rule=Complementary&selected=3&name=Kopia%20Copia%20de%20Copy%20of%20Sunset%20Camping&mode=rgb&rgbvalues=0.77,0.807843137254902,0,0.7385008800919313,0.77,0.09758355429785368,0.44798300970861415,0.47,0,0.4062004854369275,0,0.77,0.24794055604591675,0,0.47&swatchOrder=0,1,2,3,4
public:
	static sf::Color FIRST;
	static sf::Color SECOND;
	static sf::Color THIRD;
	static sf::Color FOURTH;
	static sf::Color FIFTH;
	static sf::Color WHITE;
	static sf::Color BLACK;

	static sf::Color textLitColor;
	static sf::Color backgroundColor;

	static void load();
};

#endif