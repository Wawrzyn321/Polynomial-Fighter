#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include <SFML/OpenGL.hpp>
#include <vector>

class EntityManager
{
	friend class PoolManager;
	EntityManager() = default;

    static EntityManager *sInstance;
    std::vector<std::shared_ptr<Entity>> entities;

public:

	static EntityManager *instance();

	void addEntity(std::shared_ptr<Entity>);

	void deleteEntity(std::shared_ptr<Entity>);

	std::vector<std::shared_ptr<Entity>> getEntities() const;

	std::weak_ptr<Entity> findEntityByName(std::string name);

	std::weak_ptr<Entity> findEntityByTag(std::string tag, bool includeDisabled = false);

    std::vector<std::weak_ptr<Entity>> findEntitiesByTag(std::string tag, bool includeDisabled = false);

	void update(Time::TimeData timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

	void clear();

	~EntityManager();
};


#endif