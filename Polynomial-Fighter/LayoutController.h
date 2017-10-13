#ifndef LAYOUT_CONTROLLER
#define LAYOUT_CONTROLLER

#include <SFML\Graphics.hpp>
#include "GUILabel.h"
#include <vector>
#include "Timer.h"

class LayoutController : public sf::Drawable {
public:

	enum State {
		START,
		TO_POSITION,
		FROM_POSITION,
		IDLE,
		TO_ROTATION
	};

private:

	sf::CircleShape ring;
	GUILabel *titleText;
	std::vector<GUILabel*> menuTexts;

public:

	State state;

	LayoutController(GUILabel *titleText, std::vector<GUILabel*> menuTexts);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

private:

	void initRing();

	void setupTitleTransform(GUILabel *label);

	void setupTextTransform(GUILabel* label, float radius, int angle);

	sf::Color color_ring = sf::Color(191, 251, 31);
};

#endif