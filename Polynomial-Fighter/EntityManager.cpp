#include "EntityManager.h"
#include "Debug.h"

EntityManager *EntityManager::sInstance = nullptr;

EntityManager *EntityManager::instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new EntityManager();
    }

    return sInstance;
}

std::shared_ptr<Entity>& EntityManager::addEntity(const std::shared_ptr<Entity>& entity, bool instantly)
{
	if (instantly) {
		entities.push_back(entity);
		return entities.back();
	}
	else {
		entitiesToAdd.push_back(entity);
		return entitiesToAdd.back();
	}
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

void EntityManager::deleteEntity(const std::shared_ptr<Entity> &entity)
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i] == entity)
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

std::vector<std::shared_ptr<Entity>> EntityManager::getEntities(bool includeDisabled)
{
    if (includeDisabled)
    {
        return entities;
    }

    std::vector<std::shared_ptr<Entity>> toReturn;

	for (auto &entity : entities)
    {
        if (!entity->getEnabled())
        {
            continue;
        }

        toReturn.push_back(entity);
    }

    return toReturn;
}

void EntityManager::addNewEntitites()
{
	if (!entitiesToAdd.empty()) {
		for (auto &&entity : entitiesToAdd)
		{
			entities.push_back(entity);
		}
		entitiesToAdd.clear();
	}
}

#pragma region Searching the list

std::shared_ptr<Entity> EntityManager::findEntityByName(const std::string &name)
{
	for (auto &entity : entities)
    {
		if (entity->name == name)
        {
			return entity;
		}
	}

    return {};
}

std::vector<std::shared_ptr<Entity>> EntityManager::findEntitiesByTag(const std::string &tag, bool includeDisabled)
{
	std::vector<std::shared_ptr<Entity>> entitiesFound;

	for (auto &entity : entities)
    {
		if (entity->tag == tag)
        {
			if (!includeDisabled && !entity->getEnabled()) continue;

			entitiesFound.push_back(entity);
		}
	}

	return entitiesFound;
}

#pragma endregion

void EntityManager::update(const Time::TimeData timeData)
{
	for (auto &entity : entities)
    {
		if (entity->getEnabled())
        {
			entity->update(timeData);
		}
	}
}

void EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	for (auto &entity : entities)
    {
		if (entity == nullptr)
        {
			Debug::PrintErrorFormatted("EntityManager::draw: supplied entity is NULL!");
			continue;
		}

		if (entity->getEnabled())
        {
			//todo uzmiennic
			/*glEnable(GL_SCISSOR_TEST);
			glScissor((GLint)GameData::SCENE_BOUNDS.left,
				(GLint)GameData::SCENE_BOUNDS.top,
				(GLint)GameData::SCENE_BOUNDS.width,
				(GLint)GameData::SCENE_BOUNDS.height);*/
			entity->draw(target, states);
			//glDisable(GL_SCISSOR_TEST);
		}
	}
}

void EntityManager::clear()
{
	for (auto &entity : entities)
	{
        if (entity->getEnabled())
        {
            entity->onDestroy();
        }

		entity.reset();
	}

	entities.clear();
}

EntityManager::~EntityManager()
{
	for (auto &entity : entities)
	{
        if (entity->getEnabled())
        {
            entity->onDestroy();
        }

		entity.reset();
	}

	entities.clear();
}

void EntityManager::removeMarked()
{
    std::vector<std::shared_ptr<Entity>> toDelete;

    for (auto &entity : entities)
    {
        if (entity->getToDelete())
        {
            toDelete.push_back(entity);
        }
    }

    if (!toDelete.empty())
    {
        for (auto &i : toDelete)
        {
            deleteEntity(i);
        }
    }
}

void EntityManager::deleteEntityById(unsigned long id)
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (entities[i]->getId() == id)
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

std::shared_ptr<Entity> EntityManager::findEntityById(unsigned long id)
{
    for (auto &entity : entities)
    {
        if (entity->getId() == id)
        {
            return entity;
        }
    }

    return {};
}
