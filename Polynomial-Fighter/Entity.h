#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "ITransformable.h"
//#include "EventManager.h"
#include "Timer.h"

class Entity : public sf::Drawable, public ITransformable {
protected:
    bool enabled = true;
	bool toDelete = false;
public:
    std::string name;
	std::string tag;

	Entity(const std::string &name = "", const std::string &tag = "") :
			name(name), tag(tag) {};

    virtual void update(Time::TimeData timeData) {};

    virtual void onDestroy() {};

    void setEnabled(bool enabled)
	{
        this->enabled = enabled;
    }

	bool getEnabled() const
	{
		return enabled;
	}

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {};

	bool getToDelete() const
	{
		return toDelete;
	}
	void setToDelete(bool toDelete)
	{
		this->toDelete = toDelete;
	}
};


#endif