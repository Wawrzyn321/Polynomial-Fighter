#include "GUIRing.h"
#include "Colors.h"

GUIRing::GUIRing(const sf::Vector2f &center)
{
	state = State::TO_MINOR;

	shape = sf::CircleShape(initialRadius, 128);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOrigin(initialRadius, initialRadius);
	shape.setOutlineColor(Colors::ringColor);
	shape.setPosition(center);
}

void GUIRing::update(float deltaTime)
{
	RingValues *vals = nullptr;
	switch (state) {
	case State::TO_MINOR:
		vals = &minorValues;
		break;
	case State::TO_MAJOR:
		vals = &majorValues;
		break;
	case State::EXITING:
		vals = &exitingValues;
		break;
	case State::TO_GAME:
		vals = &toGameValues;
		break;
	}

	if(vals && vals->lerpBody(shape, deltaTime))
	{
		vals->finish(shape);
		state = State::IDLE;
	}

	sf::Color color = colorWithAlpha(Colors::ringColor, state != State::TO_GAME ? 255 : 111);
	shape.setOutlineColor(lerp(shape.getOutlineColor(), color, deltaTime*0.01f));
}

void GUIRing::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}