#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "Debug.h"
#include <SFML/OpenGL.hpp>
#include <vector>

class EntityManager
{
private:
	EntityManager() = default;

    static EntityManager *sInstance;
    std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<Entity>> entitiesToAdd;
public:

	static EntityManager *instance();

	std::shared_ptr<Entity> & addEntity(const std::shared_ptr<Entity> &entity, bool instantly = false);

    template<class T>
    std::shared_ptr<T> addEntity(const std::shared_ptr<Entity> &entity);

	void deleteEntitiesByTag(const std::string &tag);

    void deleteEntityByName(const std::string &name);

	void deleteEntityById(unsigned long id);

	void deleteEntity(const std::shared_ptr<Entity> &entity);

    std::vector<std::shared_ptr<Entity>> getEntities(bool includeDisabled = false);

	void addNewEntitites();

	std::shared_ptr<Entity> findEntityByName(const std::string &name);

	std::shared_ptr<Entity> findEntityById(unsigned long id);

    std::vector<std::shared_ptr<Entity>> findEntitiesByTag(const std::string &tag, bool includeDisabled = false);

    template<class T>
    std::vector<std::shared_ptr<T>> getEntities(bool includeDisabled = false);

    template<class T>
    std::shared_ptr<T> findEntityByName(const std::string &name);

    template<class T>
    std::shared_ptr<T> findEntityById(unsigned long id);

	template <class T>
	std::shared_ptr<T> findEntityOfType(bool includeDisabled = false);

    template<class T>
    std::vector<std::shared_ptr<T>> findEntitiesByTag(const std::string &tag, bool includeDisabled = false);

	void update(const Time::TimeData &timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

	void clear();

	void removeMarked();

	~EntityManager();
};

template<class T>
std::shared_ptr<T> EntityManager::addEntity(const std::shared_ptr<Entity> &entity)
{
    entities.push_back(entity);
    return std::dynamic_pointer_cast<T>(entities.back());
}

template<class T>
std::vector<std::shared_ptr<T>> EntityManager::getEntities(bool includeDisabled)
{
    if (includeDisabled)
    {
        return entities;
    }

    std::vector<std::shared_ptr<T>> toReturn;

    for (auto &entity : entities)
    {
        if (!entity->getEnabled())
        {
            continue;
        }

        toReturn.push_back(std::dynamic_pointer_cast<T>(entity));
    }

    return toReturn;
}

template<class T>
std::shared_ptr<T> EntityManager::findEntityByName(const std::string &name)
{
    for (auto &entity : entities)
    {
        if (entity->name == name)
        {
            return std::dynamic_pointer_cast<T>(entity);
        }
    }

    return {};
}

template<class T>
std::shared_ptr<T> EntityManager::findEntityById(unsigned long id)
{
    for (auto &entity : entities)
    {
        if (entity->getId() == id)
        {
            return std::dynamic_pointer_cast<T>(entity);
        }
    }

    return {};
}

template <class T>
std::shared_ptr<T> EntityManager::findEntityOfType(bool includeDisabled)
{
	for (auto &entitie : entities) {
		if (entitie->getEnabled() || includeDisabled) {
			auto e = std::dynamic_pointer_cast<T>(entitie);
			if (e != nullptr)
			{
				return e;
			}
		}
	}
	return {};
}

template<class T>
std::vector<std::shared_ptr<T>> EntityManager::findEntitiesByTag(const std::string &tag, bool includeDisabled)
{
    std::vector<std::shared_ptr<T>> entitiesFound;

    for (auto &entity : entities)
    {
        if (entity->tag == tag)
        {
            if (!includeDisabled && !entity->getEnabled()) continue;

            entitiesFound.push_back(std::dynamic_pointer_cast<T>(entity));
        }
    }

    return entitiesFound;
}


#endif