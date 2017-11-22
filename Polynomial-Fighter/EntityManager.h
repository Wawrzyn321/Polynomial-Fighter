#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include <SFML/OpenGL.hpp>
#include <vector>

class EntityManager
{
private:
	EntityManager() = default;

    static EntityManager *sInstance;
    std::vector<std::shared_ptr<Entity>> entities;
public:

	static EntityManager *instance();

	void addEntity(const std::shared_ptr<Entity> &entity);

	void deleteEntitiesByTag(const std::string &tag);

    void deleteEntityByName(const std::string &name);

	void deleteEntityById(unsigned long id);

	void deleteEntity(const std::weak_ptr<Entity> &entity);

    std::vector<std::weak_ptr<Entity>> getEntities(bool includeDisabled = false);

	std::weak_ptr<Entity> findEntityByName(const std::string &name);

	std::weak_ptr<Entity> findEntityById(unsigned long id);

    std::vector<std::weak_ptr<Entity>> findEntitiesByTag(const std::string &tag, bool includeDisabled = false);

	void update(Time::TimeData timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

	void clear();

	void removeMarked();

	~EntityManager();
};


#endif