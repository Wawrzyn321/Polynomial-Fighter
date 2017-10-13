#ifndef IMOUSE_EVENTS_LISTENER_H
#define IMOUSE_EVENTS_LISTENER_H

#include <SFML/System/Vector2.hpp>

class IMouseEventsListener {
public:
	virtual void onMouseMove(sf::Vector2i mousePosition) = 0;

	virtual void onMouseClick(sf::Vector2i mousePosition) = 0;
};



#endif