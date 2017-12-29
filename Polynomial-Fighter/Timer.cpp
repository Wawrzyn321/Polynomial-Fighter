#include "Timer.h"

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

    sf::Uint64 Timer::getDeltaTime() const //TODO zmieni� to �adniej
    {
        return static_cast<sf::Uint64>(deltaTimeTimer->restart().asMicroseconds());
    }

    sf::Uint64 Timer::getElapsedTime() const
    {
        return static_cast<sf::Uint64>(timer->getElapsedTime().asMicroseconds());
    }

    float Timer::getTimeScale() const
    {
        return timeScale;
    }

    TimeData Timer::getTimeData() const
    {
        return {
			deltaTimeTimer->restart(),
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