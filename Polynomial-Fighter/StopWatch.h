#ifndef STOPWATCH_H
#define STOPWATCH_H
#include "Entity.h"
#include "Delegate.h"

class StopWatch : public Entity
{
	float accumulator;
	float interval;
public:
	bool isRunning;
	Delegate<void> OnTime;

	StopWatch();

	StopWatch(float interval, bool run = false);

	void reset(float interval, bool run);

	sf::Vector2f getPosition() const override;

	void setPosition(const sf::Vector2f& position) override;

	void update(const Time::TimeData& timeData) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif