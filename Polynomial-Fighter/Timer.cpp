#include "Timer.h"

namespace Time {

    Timer *Timer::sInstance = NULL;

    Timer* Time::Timer::instance() {
        if (sInstance == NULL) {
            sInstance = new Timer();
            sInstance->deltaTimeTimer = new sf::Clock();
            sInstance->timer = new sf::Clock();
        }
        return sInstance;
    }

    sf::Uint64 Timer::getDeltaTime() {
        return sInstance->deltaTimeTimer->restart().asMicroseconds();
    }

    sf::Uint64 Timer::getElapsedTime() {
        return sInstance->timer->getElapsedTime().asMicroseconds();
    }

    float Timer::getTimeScale() {
        return timeScale;
    }

    TimeData Timer::getTimeData()
    {
        return {
			sInstance->deltaTimeTimer->restart(),
			sInstance->timeScale,
			sInstance->timer->getElapsedTime()
		};
    }

    void Timer::setTimeScale(float timeScale) {
        this->timeScale = timeScale;
        if (this->timeScale < 0) {
            this->timeScale = 0;
        }
    }

	void Timer::reset() {
		sInstance->deltaTimeTimer = new sf::Clock();
		sInstance->timer = new sf::Clock();
	}

}