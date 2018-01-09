#include "GUIAnimator.h"

GUIAnimator::GUIAnimator(tgui::Gui *gui)
{
	this->gui = gui;
}

void GUIAnimator::update(const Time::TimeData& timeData)
{
	ring.update(timeData);
}

void GUIAnimator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(ring, states);
}
