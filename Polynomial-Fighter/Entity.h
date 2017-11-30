#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Timer.h"

class Entity : public sf::Drawable, public sf::Transformable {
private:
	unsigned long getCurrentId()
	{
		static unsigned long currentId = 0;
		return currentId++;
	}
protected:
    bool enabled = true;
	bool toDelete = false;
	const unsigned long id;
	float collisionRadius = 0;
	virtual bool checkCollision(Entity &other);
    sf::Vector2f position;
public:
    std::string name;
	std::string tag;
	bool collisionsEnabled = true;

	Entity(const std::string &name = "", const std::string &tag = "") :
			name(name), tag(tag), id(getCurrentId()) {};

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

	unsigned long getId() const
	{
		return id;
	}

	virtual sf::Vector2f getPosition() const;
	virtual void setPosition(sf::Vector2f position) = 0;
	virtual float getCollisionRadius() const;
};

#endif