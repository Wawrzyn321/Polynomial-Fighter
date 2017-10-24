#include "EntityManager.h"

EntityManager *EntityManager::sInstance = nullptr;

EntityManager * EntityManager::instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new EntityManager();
    }

    return sInstance;
}

void EntityManager::addEntity(std::shared_ptr<Entity> entity)
{
	entities.push_back(entity);
}

void EntityManager::deleteEntitiesByTag(const std::string &tag)
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->tag == tag)
        {
            if (entities[i]->getEnabled())
            {
                entities[i]->onDestroy();
            }

            entities[i].reset();
            entities.erase(entities.begin() + i);
        }
    }
}

void EntityManager::deleteEntityByName(const std::string &name)
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->name == name)
        {
            if (entities[i]->getEnabled())
            {
                entities[i]->onDestroy();
            }

            entities[i].reset();
            entities.erase(entities.begin() + i);
            return;
        }
    }
}

std::vector<std::weak_ptr<Entity>> EntityManager::getEntities()
{
    std::vector<std::weak_ptr<Entity>> weakPtrs;

	for (auto &entitie : entities)
    {
        std::weak_ptr<Entity> weakPtr = entitie;
        weakPtrs.push_back(weakPtr);
    }

    return weakPtrs;
}

#pragma region Searching the list

std::weak_ptr<Entity> EntityManager::findEntityByName(const std::string &name)
{
	for (auto &entitie : entities)
    {
		if (entitie->name == name)
        {
            std::weak_ptr<Entity> weakPtr = entitie;
			return weakPtr;
		}
	}
    //Debug::PrintFormatted("EntityManager::findEntityByName: could not find object of name <%>!\n", name);
    return std::weak_ptr<Entity>(); //sprawdza sie to std::weak_ptr::expired(), bo nie da sie nullptr
}

std::vector<std::weak_ptr<Entity>> EntityManager::findEntitiesByTag(const std::string &tag, bool includeDisabled)
{
	std::vector<std::weak_ptr<Entity>> entitiesFound;

	for (auto &entitie : entities)
    {
		if (entitie->tag == tag)
        {
			if (!includeDisabled && !entitie->getEnabled()) continue;
            std::weak_ptr<Entity> weakPtr = entitie;
			entitiesFound.push_back(weakPtr);
		}
	}

	return entitiesFound;
}

#pragma endregion

void EntityManager::update(const Time::TimeData timeData)
{
	for (auto &entitie : entities)
    {
		if (entitie->getEnabled())
        {
			entitie->update(timeData);
		}
	}
}

void EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states) {
	for (auto &entitie : entities) {
		if (entitie == nullptr) {
			Debug::PrintErrorFormatted("EntityManager::draw: supplied entity is NULL!");
			continue;
		}
		if (entitie->getEnabled()) {

			//todo uzmienni?
			/*glEnable(GL_SCISSOR_TEST);
			glScissor((GLint)GameData::SCENE_BOUNDS.left,
				(GLint)GameData::SCENE_BOUNDS.top,
				(GLint)GameData::SCENE_BOUNDS.width,
				(GLint)GameData::SCENE_BOUNDS.height);*/
			entitie->draw(target, states);
			//glDisable(GL_SCISSOR_TEST);
		}
	}
}

void EntityManager::clear()
{
	for (auto &entity : entities)
	{
		entity->onDestroy();
		entity.reset();
	}
	entities.clear();
}

EntityManager::~EntityManager()
{
	for (auto &entity : entities)
	{
		entity->onDestroy();
		entity.reset();
	}
	entities.clear();
}