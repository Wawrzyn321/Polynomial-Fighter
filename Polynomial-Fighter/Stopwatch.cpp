#include "StopWatch.h"
#include "Debug.h"

StopWatch::StopWatch()
{
	interval = 0;
	accumulator = 0;
	isRunning = false;
}

StopWatch::StopWatch(float interval, bool run)
{
	this->interval = interval;

	isRunning = run;
	accumulator = 0;
}

void StopWatch::reset(float interval, bool run)
{
	this->interval = interval;

	isRunning = run;
	accumulator = 0;
}

sf::Vector2f StopWatch::getPosition() const
{
	return {};
}

void StopWatch::setPosition(const sf::Vector2f& position)
{
	return;
}

void StopWatch::update(const Time::TimeData& timeData)
{
	if (isRunning) {
		accumulator += timeData.getScaledDeltaTimeInMili();
		if (accumulator > interval)
		{
			OnTime();
			isRunning = false;
		}
	}
}

void StopWatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	return;
}
