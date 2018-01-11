#include "Timer.h"
#include "SoundManager.h"

namespace Time {

    Timer *Timer::sInstance = nullptr;

    Timer* Timer::instance() {
        if (sInstance == nullptr) {
            sInstance = new Timer();
            sInstance->deltaTimeTimer = new sf::Clock();
            sInstance->timer = new sf::Clock();
        }
        return sInstance;
    }

    float Timer::getTimeScale() const
    {
        return timeScale;
    }

    TimeData Timer::getTimeData() const
    {
		sf::Time deltaTime = deltaTimeTimer->restart();
		if (deltaTime.asMilliseconds() > maximumTimestep)
		{
			deltaTime = sf::milliseconds(maximumTimestep);
		}
        return {
			deltaTime,
			timeScale,
			timer->getElapsedTime()
		};
    }

    void Timer::setTimeScale(float timeScale)
    {
        this->timeScale = timeScale;
        if (this->timeScale < 0)
        {
            this->timeScale = 0;
        }
		SoundManager::instance()->setPitch(timeScale);
    }

	void Timer::reset() const
	{
		deltaTimeTimer->restart();
		timer->restart();
	}

}
