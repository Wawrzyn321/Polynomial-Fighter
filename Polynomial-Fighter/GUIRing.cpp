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
	switch (state) {
	case State::TO_MINOR:
		if (minorValues.lerpBody(shape, deltaTime))
		{
			minorValues.finish(shape);
			state = State::IDLE;
		}
		break;
	case State::TO_MAJOR:
		if (majorValues.lerpBody(shape, deltaTime))
		{
			majorValues.finish(shape);
			state = State::IDLE;
		}
		break;
	case State::EXITING:
		if (exitingValues.lerpBody(shape, deltaTime))
		{
			exitingValues.finish(shape);
			state = State::IDLE;
		}
		break;
	default:
		break;
	}
}

void GUIRing::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}
