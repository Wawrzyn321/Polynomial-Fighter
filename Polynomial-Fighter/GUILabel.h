#ifndef GUI_LABEL_H
#define GUI_LABEL_H

#include <functional>
#include "Asset Manager.h"
#include "Timer.h"

class PauseManager;

class GUILabel : public sf::Drawable {
	friend class PauseManager;
protected:
	sf::Text text;
	std::function<void(void)> action = nullptr;

	bool mouseCollideText(const sf::Vector2i& pos);

	void playClick();

public:

	GUILabel(sf::Vector2f position, int fontSize, std::string caption, std::function<void(void)> function = nullptr);

	virtual void update(const Time::TimeData &timeData);

	void updateText(const std::string &caption);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const;

protected:
	sf::Color color_text_normal = sf::Color::White;
	sf::Color color_text_highlight = sf::Color(240,7,7);
	sf::Color currentColor = color_text_normal;
};

#endif