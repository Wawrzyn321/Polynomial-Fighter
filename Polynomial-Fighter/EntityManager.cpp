#include "EntityManager.h"

EntityManager *EntityManager::sInstance = NULL;

EntityManager * EntityManager::instance()
{
    if (sInstance == NULL) {
        sInstance = new EntityManager();
    }
    return sInstance;
}

void EntityManager::addEntity(Entity *entity) {
	entities.push_back(entity);
}

void EntityManager::deleteEntity(Entity *entity) {
	if (entity == NULL) {
		Debug::PrintErrorFormatted("EntityManager::deleteEntity: supplied Entity was NULL!");
		return;
	}
	if (entity->getEnabled()) {
		entity->onDestroy();
	}
	entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
	delete entity;
    entity = NULL;
}

std::vector<Entity*> EntityManager::getEntities() {
	return entities;
}

#pragma region Searching the list

Entity* EntityManager::findEntityByName(std::string name) {
	for (unsigned i = 0; i < entities.size(); i++) {
		if (entities[i]->name == name) {
			return entities[i];
		}
	}
    //Debug::PrintFormatted("EntityManager::findEntityByName: could not find object of name <%>!\n", name);
	return NULL;
}

Entity* EntityManager::findEntityByTag(std::string tag, bool includeDisabled) {
	for (unsigned i = 0; i < entities.size(); i++) {
		if (entities[i]->getEnabled() == false && !includeDisabled) continue;
		if (entities[i]->tag == tag) {
			return entities[i];
		}
	}
	return NULL;
}

std::vector<Entity*> EntityManager::findEntitiesByTag(std::string tag, bool includeDisabled) {
	std::vector<Entity*> entitiesFound;
	for (unsigned i = 0; i < entities.size(); i++) {
		if (entities[i]->tag == tag) {
			if (!includeDisabled && entities[i]->getEnabled() == false) continue;
			entitiesFound.push_back(entities[i]);
		}
	}
	return entitiesFound;
}

#pragma endregion

void EntityManager::update(Time::TimeData timeData) {
	Time::Timer *t = Time::Timer::instance();
	for (unsigned i = 0; i < entities.size(); i++) {
		if (entities[i]->getEnabled()) {
			entities[i]->update(timeData);
		}
	}
}

void EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states) {
	for (unsigned i = 0; i < entities.size(); i++) {
		if (entities[i] == NULL) {
			Debug::PrintErrorFormatted("EntityManager::draw: supplied entity is NULL!");
			continue;
		}
		if (entities[i]->getEnabled()) {
			glEnable(GL_SCISSOR_TEST);
			glScissor((GLint)GameData::SCENE_BOUNDS.left,
				(GLint)GameData::SCENE_BOUNDS.top,
				(GLint)GameData::SCENE_BOUNDS.width,
				(GLint)GameData::SCENE_BOUNDS.height);
			entities[i]->draw(target, states);
			glDisable(GL_SCISSOR_TEST);
		}
	}
}

void EntityManager::reset()
{
	for (unsigned i = 0; i < entities.size(); i++) {
		delete entities[i];
		entities[i] = NULL;
	}
	entities.clear();
}

bool EntityManager::validateEntityIndex(Entity* entity) {
	if (entity == NULL) return false;
	for (unsigned i = 0; i < entities.size(); i++) {
		if (entities[i] == entity) {
			return true;
		}
	}
	return false;
}

EntityManager::~EntityManager() {
	for (unsigned i = 0; i < entities.size(); i++) {
		entities[i]->onDestroy();
		delete entities[i];
	}
}