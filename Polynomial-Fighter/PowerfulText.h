#ifndef POWERFUL_TEXT_H
#define POWERFUL_TEXT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class PowerfulText : public sf::Drawable
{
	sf::Color color;
	sf::Vector2f position;
	unsigned characterSize;

	std::string script;
	std::vector<sf::Text> texts;
	std::shared_ptr<sf::Font> font;

	float overallLength;
	bool isCentered;
public:

	PowerfulText(){}

	PowerfulText(const std::string& script, const std::shared_ptr<sf::Font> &font, unsigned characterSize = 30);

	void rebuild(const std::string& script, bool autoRecenter = false);

	void center();

	sf::Color getColor() const;
	void setColor(const sf::Color &color);

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f &position);

	int getCharacterSize() const;
	void setCharacterSize(unsigned characterSize);

	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
private:
	const char UPPER = '^';
	const char LOWER = '_';
	const float LOWER_SHIFT = -0.5f;
	const float UPPER_SHIFT = 0.3f;
	const float SIZE_MULTIPLIER = 0.8f;
	const float MID_TEXT_OFFSET = 0.12f;
};

#endif
