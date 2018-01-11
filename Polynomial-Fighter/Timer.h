#ifndef TIMER_H
#define TIMER_H

#include <SFML/System.hpp>

namespace Time {

    const float MICRO_TO_MILI = 0.001f;
    const float MICRO_TO_SEC = 0.001f * 0.001f;
	const sf::Int64 maximumTimestep = 30;

    struct TimeData {
        sf::Time deltaTime;
        float timeScale{};
        sf::Time elapsedTime;
        float getScaledDeltaTimeInMili() const
        {
			return deltaTime.asMicroseconds() * timeScale * MICRO_TO_MILI;
        }
        float getScaledDeltaTimeInSec() const
        {
            return deltaTime.asMicroseconds() * timeScale * MICRO_TO_SEC;
        }
    };

    class Timer {
        static Timer *sInstance;
        sf::Clock *deltaTimeTimer{};
        sf::Clock *timer{};
        float timeScale = 1;
    public:
        static Timer* instance();
        void setTimeScale(float timeScale);
        float getTimeScale() const;
        TimeData getTimeData() const;
		void reset() const;
    };

}
#endif