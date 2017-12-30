#ifndef CAMERA_SHAKE
#define CAMERA_SHAKE
#include "Timer.h"
#include "Debug.h"

class CameraShake
{
	sf::RenderWindow *window = nullptr;
	sf::View defaultView;
	bool isShaking = false;
	float durationAccumulator = 0;
	float force = 0;
	float duration = 0;

	sf::Vector2f getShakeAmount(float percentageCompleted) const;

	void shakeCamera() const;

	void finishShaking();
public:
	void shake(float force = 2.0f, float duration = 50.0f);

	void update(const Time::TimeData& timeData);

	void connectWindow(sf::RenderWindow* window);
};

#endif