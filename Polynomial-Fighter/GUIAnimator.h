#ifndef GUI_ANIMATOR_H
#define GUI_ANIMATOR_H
#include <memory>
#include <TGUI/Gui.hpp>
#include "Timer.h"
#include "GUIRing.h"

class GUIAnimator
{
public:
	tgui::Gui *gui;
	GUIRing ring;
public:
	GUIAnimator(tgui::Gui *gui);

	void update(const Time::TimeData& timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
};

#endif