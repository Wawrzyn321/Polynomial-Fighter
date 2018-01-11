#include "CameraShake.h"
#include "Utility.h"

sf::Vector2f CameraShake::getShakeAmount(float percentageCompleted) const
{
	float damper = 1.0f - clamp(4.0f * percentageCompleted - 3.0f, 0.0f, 1.0f);
	float x = RandomGenerator::getFloat(0.0f, 1.0f) * 2.0f - 1.0f;
	float y = RandomGenerator::getFloat(0.0f, 1.0f) * 2.0f - 1.0f;
	x *= force * damper;
	y *= force * damper;

	return { defaultView.getCenter().x + x, defaultView.getCenter().y + y };
}

void CameraShake::shakeCamera() const
{
	sf::Vector2f shake = getShakeAmount(durationAccumulator / duration);
	sf::View view = sf::View(shake, defaultView.getSize());
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
