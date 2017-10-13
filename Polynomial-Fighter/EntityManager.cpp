#include "EntityManager.h"

EntityManager *EntityManager::sInstance = nullptr;

EntityManager * EntityManager::instance()
{
    if (sInstance == nullptr) {
        sInstance = new EntityManager();
    }
    return sInstance;
}

void EntityManager::addEntity(Entity *entity) {
	entities.push_back(entity);
}

void EntityManager::deleteEntity(Entity *entity) {
	if (entity == nullptr) {
		Debug::PrintErrorFormatted("EntityManager::deleteEntity: supplied Entity was NULL!");
		return;
	}
	if (entity->getEnabled()) {
		entity->onDestroy();
	}
	entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
	delete entity;
    entity = nullptr;
}

std::vector<Entity*> EntityManager::getEntities() {
	return entities;
}

#pragma region Searching the list

Entity* EntityManager::findEntityByName(std::string name) {
	for (auto &entitie : entities) {
		if (entitie->name == name) {
			return entitie;
		}
	}
    //Debug::PrintFormatted("EntityManager::findEntityByName: could not find object of name <%>!\n", name);
	return nullptr;
}

Entity* EntityManager::findEntityByTag(std::string tag, bool includeDisabled) {
	for (auto &entitie : entities) {
		if (!entitie->getEnabled() && !includeDisabled) continue;
		if (entitie->tag == tag) {
			return entitie;
		}
	}
	return nullptr;
}

std::vector<Entity*> EntityManager::findEntitiesByTag(std::string tag, bool includeDisabled)
{
	std::vector<Entity*> entitiesFound;
	for (auto &entitie : entities) {
		if (entitie->tag == tag) {
			if (!includeDisabled && !entitie->getEnabled()) continue;
			entitiesFound.push_back(entitie);
		}
	}
	return entitiesFound;
}

#pragma endregion

void EntityManager::update(Time::TimeData timeData) {
	Time::Timer *t = Time::Timer::instance();
	for (auto &entitie : entities) {
		if (entitie->getEnabled()) {
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
			glEnable(GL_SCISSOR_TEST);
			glScissor((GLint)GameData::SCENE_BOUNDS.left,
				(GLint)GameData::SCENE_BOUNDS.top,
				(GLint)GameData::SCENE_BOUNDS.width,
				(GLint)GameData::SCENE_BOUNDS.height);
			entitie->draw(target, states);
			glDisable(GL_SCISSOR_TEST);
		}
	}
}

void EntityManager::reset()
{
	for (auto &entitie : entities) {
		delete entitie;
		entitie = nullptr;
	}
	entities.clear();
}

bool EntityManager::validateEntityIndex(Entity* entity) {
	if (entity == nullptr) return false;
	for (auto &entitie : entities) {
		if (entitie == entity) {
			return true;
		}
	}
	return false;
}

EntityManager::~EntityManager() {
	for (auto &entitie : entities) {
		entitie->onDestroy();
		delete entitie;
	}
}