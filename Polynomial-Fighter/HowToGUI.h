#ifndef HOW_TO_GUI_H
#define HOW_TO_GUI_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Utility.h"

struct HowToEntry
{
	sf::Text text;
	sf::Vector2f targetPosition;
	float targetScale;

	HowToEntry(sf::Text text, const sf::Vector2f &targetPosition, float targetScale)
	{
		this->text = text;
		this->targetPosition = targetPosition;
		this->targetScale = targetScale;
	}

	void update(float deltaTime)
	{
		text.setPosition(lerp(text.getPosition(), targetPosition, deltaTime));
		float s = lerp(text.getScale().x, targetScale, deltaTime);
		text.setScale(s, s);
	}
};

class HowToGUI : public sf::Drawable
{
public:
	enum class State {
		IDLE,
		HIDING,
		MOVING,
	};
private:
	State state;
	std::vector<HowToEntry*> entries;
	std::shared_ptr<sf::Font> font;
	int currentlyCentered = 0;
	sf::Vector2f center;
public:
	HowToGUI(const sf::Vector2f &center);

	void moveUp();

	void moveDown();

	void setVisible(bool visible);

	void update(float deltaTime);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	~HowToGUI();
};


#endif
