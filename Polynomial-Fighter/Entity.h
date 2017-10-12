#ifndef ENTITY_H
#define ENTITY_H

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "ITransformable.h"
//#include "EventManager.h"
#include "Timer.h"

class Entity : public sf::Drawable, public ITransformable {
protected:
    bool enabled = true;
public:
    std::string name;
	std::string tag;

    virtual void update(Time::TimeData timeData) {};

    virtual void onDestroy() {};

    virtual void setEnabled(bool enabled) {
        this->enabled = enabled;
    }

	virtual bool getEnabled() {
		return enabled;
	}

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {};

};


#endif