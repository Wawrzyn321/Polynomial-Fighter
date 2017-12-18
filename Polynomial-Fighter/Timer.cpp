#include "Timer.h"

namespace Time {

    Timer *Timer::sInstance = nullptr;

    Timer* Time::Timer::instance() {
        if (sInstance == nullptr) {
            sInstance = new Timer();
            sInstance->deltaTimeTimer = new sf::Clock();
            sInstance->timer = new sf::Clock();
        }
        return sInstance;
    }

    sf::Uint64 Timer::getDeltaTime() const //TODO zmieniæ to ³adniej
    {
        return sInstance->deltaTimeTimer->restart().asMicroseconds();
    }

    sf::Uint64 Timer::getElapsedTime() const
    {
        return sInstance->timer->getElapsedTime().asMicroseconds();
    }

    float Timer::getTimeScale() const
    {
        return timeScale;
    }

    TimeData Timer::getTimeData() const
    {
        return {
			sInstance->deltaTimeTimer->restart(),
			sInstance->timeScale,
			sInstance->timer->getElapsedTime()
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

	void Timer::reset()
    {
		sInstance->deltaTimeTimer = new sf::Clock();
		sInstance->timer = new sf::Clock();
	}

}