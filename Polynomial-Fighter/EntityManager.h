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

	void addEntity(std::shared_ptr<Entity>);

    //latwiej nam bedzie zrobic delete by name/tag
    //zreszta chyba bedzie to mialo wiecej sensu logicznego
	void deleteEntitiesByTag(const std::string &tag);

    void deleteEntityByName(const std::string &name);

    std::vector<std::weak_ptr<Entity>> getEntities();

	std::weak_ptr<Entity> findEntityByName(const std::string &name);

    //ta funkcja troche nie ma sensu chyba, tag z definicji okresla grupe obiektow
    //chyba, ze czasem sie przyda wziecie pierwszego z brzegu z danego tagu
	std::weak_ptr<Entity> findEntityByTag(const std::string &tag, bool includeDisabled = false);

    std::vector<std::weak_ptr<Entity>> findEntitiesByTag(const std::string &tag, bool includeDisabled = false);

	void update(Time::TimeData timeData);

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

	void clear();

	~EntityManager();
};


#endif