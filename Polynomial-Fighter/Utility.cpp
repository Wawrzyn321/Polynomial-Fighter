#include "Utility.h"

unsigned intLenght(int number) {
	int l = 0;

	if (number < 0) {
		number = -number;
		l++; //if negative, add 1 for sign
	}

	while (number) {
		l++;
		number /= 10;
	}

	return l;
}

void centerTextOrigin(sf::Text & textShape)
{
	textShape.setOrigin(textShape.getLocalBounds().width / 2, textShape.getLocalBounds().height / 2);
}

void setAlpha(sf::Shape &shape, float alpha)
{
	sf::Color c = shape.getFillColor();
	shape.setFillColor(sf::Color((sf::Uint8)c.r, (sf::Uint8)c.g, (sf::Uint8)c.b, (sf::Uint8)alpha));
}

void setAlpha(sf::Sprite &sprite, float alpha)
{
	sf::Color c = sprite.getColor();
	sprite.setColor(sf::Color((sf::Uint8)c.r, (sf::Uint8)c.g, (sf::Uint8)c.b, (sf::Uint8)alpha));
}

void setAlpha(sf::Text &text, float alpha) {
	sf::Color c = text.getFillColor();
	text.setFillColor(sf::Color((sf::Uint8)c.r, (sf::Uint8)c.g, (sf::Uint8)c.b, (sf::Uint8)alpha));
}

sf::Color lerp(sf::Color from, sf::Color to, float amount)
{
	return sf::Color((sf::Uint8)(from.r + (to.r - from.r)*amount),
		(sf::Uint8)(from.g + (to.g - from.g)*amount),
		(sf::Uint8)(from.b + (to.b - from.b)*amount),
		(sf::Uint8)(from.a + (to.a - from.a)*amount));
}

sf::FloatRect getCenteredFloatRect(float width, float height, float xShift, float yShift)
{
	float left = (GameData::WINDOW_SIZE.x - width)*0.5f + xShift;
	float top = (GameData::WINDOW_SIZE.y - height)*0.5f + yShift;
	return sf::FloatRect(left, top, width, height);
}

int getLastCharacterPosition(std::string text, char c) {
	for (size_t i = text.size()-1; i >=0; i--) {
		if (text[i] == c) {
			return (int)i;
		}
	}
	return -1;
}
