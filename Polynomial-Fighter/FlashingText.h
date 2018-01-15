#ifndef FLASHING_TEXT_H
#define FLASHING_TEXT_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "Timer.h"
#include "FloatColor.h"

class FlashingText : public sf::Drawable
{
public:
	enum class State
	{
		IDLE,
		TO_POS_1,
		TO_POS_2,
	};
private:
	sf::Vector2f pos1;
	sf::Vector2f pos2;

	FloatColor currentColor;

	std::shared_ptr<sf::Font> font;

	void flash(float elapsedTime);

	void handleMovement(float deltaTime);
public:
	sf::Text text;
	bool canFlash;
	State state;
	FlashingText(const std::string &caption, const sf::Vector2f& position, unsigned fontSize);

	void setStateValues(const sf::Vector2f& pos1, const sf::Vector2f& pos2);

	void update(const Time::TimeData &timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	const float lerpSpeed = 0.007f;
	const float vector2Threshold = 0.1f;
	const float flashingSpeed = 2.5f;
};

#endif