#include "CameraShake.h"
#include "RandomGenerator.h"

sf::Vector2f CameraShake::getShakeAmount(float percentageCompleted) const
{
	float damper = 1.5f - percentageCompleted;
	float x = RandomGenerator::getFloat(0.0f, 1.0f) * 2.0f - 1.0f;
	float y = RandomGenerator::getFloat(0.0f, 1.0f) * 2.0f - 1.0f;
	x *= force * damper;
	y *= force * damper;

	return { x, y };
}

void CameraShake::shakeCamera() const
{
	sf::Vector2f center = defaultView.getCenter() + getShakeAmount(durationAccumulator / duration);
	sf::View view = sf::View(center, defaultView.getSize());
	window->setView(view);
}

void CameraShake::finishShaking()
{
	window->setView(defaultView);

	isShaking = false;
	durationAccumulator = 0;
	duration = 0;
}

void CameraShake::shake(float force, float duration)
{
	this->force = force;
	this->duration += duration;

	isShaking = true;
}

void CameraShake::update(const Time::TimeData& timeData)
{
	if (isShaking)
	{
		durationAccumulator += timeData.getScaledDeltaTimeInMili();

		shakeCamera();

		if (durationAccumulator > duration)
		{
			finishShaking();
		}
	}
}

void CameraShake::connectWindow(sf::RenderWindow* window)
{
	this->window = window;
	defaultView = window->getDefaultView();
}
