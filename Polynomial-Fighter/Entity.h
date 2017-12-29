#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Timer.h"
#include <memory>

class Entity : public sf::Drawable, public sf::Transformable {
	unsigned long getCurrentId()
	{
		static unsigned long currentId = 0;
		return currentId++;
	}
	bool enabled = true;
	bool toDelete = false;
protected:
	const unsigned long id;
	float collisionRadius = 0;
	virtual bool checkCollision(const std::shared_ptr<Entity> &other);
public:
    std::string name;
	std::string tag;
	bool collisionsEnabled = true;

	explicit Entity(const std::string &name = "", const std::string &tag = "") :
			name(name), tag(tag), id(getCurrentId()) {};

    virtual void update(const Time::TimeData &timeData) {};

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

	virtual sf::Vector2f getPosition() const = 0;
	virtual void setPosition(const sf::Vector2f &position) = 0;
	virtual float getCollisionRadius() const;

	Entity(const Entity&) = default;
	Entity(Entity&&) = default;
	virtual ~Entity() = default;
};

#endif