#ifndef ANIMATED_TEXT_H
#define ANIMATED_TEXT_H
#include <SFML/Graphics.hpp>
#include <memory>

namespace Time {
	struct TimeData;
}

class TitleText : public sf::Drawable
{
public:
	enum class State
	{
		IDLE,
		MENU,
		SPLASH,
		EXITING,
		UP,
	};
private:
	sf::Vector2f pos1;
	sf::Vector2f pos2;

	sf::Text text;
	std::shared_ptr<sf::Font> font;
public:
	State state;
	TitleText(const std::string &caption, const sf::Vector2f& position, unsigned fontSize);

	void setStateValues(const sf::Vector2f& pos1, const sf::Vector2f& pos2);

	void update(float deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	const float lerpSpeed = 0.007f;
	const float vector2Threshold = 0.1f;
	//const float outlineThickness = 0.1f;
};

#endif