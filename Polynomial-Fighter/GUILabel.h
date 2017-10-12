#ifndef GUI_LABEL_H
#define GUI_LABEL_H

#include <functional>
#include "IMouseEventsListener.h"
#include "Asset Manager.h"
#include "Timer.h"
class PauseManager;

class GUILabel : public sf::Drawable, public IMouseEventsListener {
	friend class PauseManager;
protected:
	sf::Text text;
	std::function<void(void)> action = NULL;

	bool mouseCollideText(sf::Vector2i pos);

	void playClick();

public:

	GUILabel() {}
	GUILabel(sf::Vector2f position, int fontSize, std::string caption, std::function<void(void)> function = NULL);

	virtual void update(Time::TimeData timeData);

	void updateText(std::string caption);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

	void onMouseClick(sf::Vector2i mousePosition);

	void onMouseMove(sf::Vector2i mousePosition);

protected:
	sf::Color color_text_normal = sf::Color::White;
	sf::Color color_text_highlight = sf::Color(240,7,7);
	sf::Color currentColor = color_text_normal;
};

#endif