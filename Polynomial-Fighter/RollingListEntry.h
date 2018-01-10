#ifndef ROLLING_LIST_ENTRY_H
#define ROLLING_LIST_ENTRY_H
#include <SFML/Graphics.hpp>

class RollingListEntry
{
public:
	sf::Text text;
	sf::Vector2f targetPosition;
	float targetScale;
	sf::Color targetColor;

	RollingListEntry(sf::Text text, sf::Vector2f targetPosition);

	void update(float deltaTime);
};

#endif