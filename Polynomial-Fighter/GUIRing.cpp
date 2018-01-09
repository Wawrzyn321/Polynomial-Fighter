#include "GUIRing.h"

GUIRing::GUIRing()
{
	state = State::TO_MINOR;

	shape = sf::CircleShape(initialRadius, 128);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOrigin(initialRadius, initialRadius);
	shape.setOutlineColor(sf::Color::Red);
}

void GUIRing::update(const Time::TimeData& timeData)
{
	float deltaTime = timeData.getScaledDeltaTimeInMili();

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
	default:
		break;
	}
}

void GUIRing::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
}
