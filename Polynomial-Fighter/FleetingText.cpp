#include "FleetingText.h"
#include "Utility.h"

void FleetingText::fadeText(float deltaTime)
{
	const float minColorDifference = 0.01f;

	currentColor = currentColor.lerpTo(sf::Color::Transparent, fadingSpeed*deltaTime);
	text.setFillColor(currentColor.toColor());
	if (currentColor.calculateMaxDifference(sf::Color::Transparent, true) < minColorDifference)
	{
		setToDelete(true);
	}
}

void FleetingText::moveText(float deltaTime)
{
	setPosition(getPosition() + velocity*deltaTime);
}

FleetingText::FleetingText(const std::string& caption, const sf::Vector2f& position, const sf::Color& color, unsigned fontSize)
{
	font = AssetManager::instance()->getDefaultFont();
	text = sf::Text(caption, *font, fontSize);
	centerTextOrigin(text);
	text.setPosition(position);

	state = State::IDLE;
	currentColor = color;
}

void FleetingText::run(float fadingSpeed, const sf::Vector2f &velocity, float waitTime, bool moveWhileWaiting)
{
	this->fadingSpeed = fadingSpeed;
	this->velocity = velocity;
	this->waitTime = waitTime;
	this->moveWhileWaiting = moveWhileWaiting;

	state = waitTime > 0 ? State::WAITING : State::MOVING;
}

sf::Vector2f FleetingText::getPosition() const
{
	return text.getPosition();
}

void FleetingText::setPosition(const sf::Vector2f& position)
{
	text.setPosition(position);
}

void FleetingText::update(const Time::TimeData& timeData)
{
	float deltaTime = timeData.getScaledDeltaTimeInMili();

	if (state == State::WAITING) {
		accumulator += deltaTime;
		if (accumulator >= waitTime)
		{
			state = State::MOVING;
		}

		if (moveWhileWaiting)
		{
			moveText(deltaTime);
		}
	}
	else if (state == State::MOVING)
	{
		moveText(deltaTime);
		fadeText(deltaTime);
	}
}

void FleetingText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//use BlendAdd to enable the transparency fo the text
	target.draw(text, sf::BlendAdd);
}
