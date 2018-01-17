#ifndef TEXT_ARROWS_H
#define TEXT_ARROWS_H
#include <SFML/Graphics.hpp>
#include "Timer.h"
#include <memory>
#include "AssetManager.h"

class TextArrows : public sf::Drawable
{
	float xRight;
	float xLeft;

	std::shared_ptr<sf::Font> font;

	sf::Text leftArrow;
	sf::Text rightArrow;
public:
	TextArrows(unsigned fontSize);

	void updateBounds(const sf::Text *text);

	void updateBounds(float xLeft, float xRight);

	void update(const Time::TimeData& time_data);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	const float yPosition = GameData::WINDOW_SIZE.y*0.47f;
};

#endif
