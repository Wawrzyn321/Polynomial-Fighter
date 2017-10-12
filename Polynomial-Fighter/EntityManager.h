#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include <SFML/OpenGL.hpp>
#include <algorithm>
#include <vector>

class EntityManager {
	friend class PoolManager;
private:
	EntityManager() {}
    static EntityManager *sInstance;
    std::vector<Entity*> entities;

public:

	static EntityManager *instance();

	void addEntity(Entity *entity);

	void deleteEntity(Entity *entity);

	std::vector<Entity*> getEntities();

	Entity* findEntityByName(std::string name);

	Entity* findEntityByTag(std::string tag, bool includeDisabled = false);

    std::vector<Entity*> findEntitiesByTag(std::string tag, bool includeDisabled = false);

	void update(Time::TimeData timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

	void reset();

	bool validateEntityIndex(Entity* entity);

	~EntityManager();
};


#endif