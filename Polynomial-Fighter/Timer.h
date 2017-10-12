#ifndef TIMER_H
#define TIMER_H

#include <SFML\System.hpp>
#include "SoundManager.h"

namespace Time {

    const float MICRO_TO_MILI = 0.001f;
    const float MICRO_TO_SEC = 0.001f*0.001f;

    struct TimeData {
        sf::Time deltaTime;
        float timeScale;
        sf::Time elapsedTime;
        float getScaledDeltaTimeInMili() {
            return deltaTime.asMicroseconds()*timeScale*MICRO_TO_MILI;
        }
        float getScaledDeltaTimeInSec() {
            return deltaTime.asMicroseconds()*timeScale*MICRO_TO_SEC;
        }
    };

    class Timer {
    private:
        static Timer *sInstance;
        sf::Clock *deltaTimeTimer;
        sf::Clock *timer;
        float timeScale = 1;
    public:
        static Timer* instance();
        sf::Uint64 getDeltaTime(); //todo const correct
        sf::Uint64 getElapsedTime();
        void setTimeScale(float timeScale);
        float getTimeScale();
        TimeData getTimeData();
		void reset();
    };

}
#endif