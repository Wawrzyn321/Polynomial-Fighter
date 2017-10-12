#ifndef SCORESMANAGERGUI_H
#define SCORESMANAGERGUI_H

#include "Utility.h"

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include "Asset Manager.h"

class ScoreManagerGUI : public sf::Drawable {
private:
	sf::RectangleShape background;
	sf::Text titleText;
	std::vector<sf::Text> scoresTexts;

	int dots = 9;
	unsigned capacity;
public:
	ScoreManagerGUI() {}
	ScoreManagerGUI(sf::Vector2f position, unsigned capacity, float scaleX = 1);

	void updateScores(std::vector<int> &scores);

	unsigned getCapacity();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Color color_backgroundFill = sf::Color::Black;
	sf::Color color_backroundOutline = sf::Color::White;
	sf::Color color_text = sf::Color::White;
};

#endif