#include "SoundManager.h"

#include <iostream>
using namespace std;

SoundManager *SoundManager::sInstance = NULL;

void SoundManager::play(sf::Sound * sound, sf::SoundBuffer *buffer)
{
	sound->setBuffer(*buffer);
	sound->play();
}

SoundManager * SoundManager::instance()
{
	if (sInstance == NULL) {
		sInstance = new SoundManager();
		sInstance->assetManagerInstance = AssetManager::instance();
	}
	return sInstance;
}

void SoundManager::playSound(std::string bufferName)
{
	if (!isOn) return;

	sf::SoundBuffer *buffer = assetManagerInstance->getSound(bufferName);

	for (unsigned i = 0; i < players.size(); i++) {
		if (players[i].getStatus() != sf::SoundSource::Status::Playing) {
			play(&players[i], buffer);
			return;
		}
	}
	sf::Sound s;
	players.push_back(s);
	play(&players.back(), buffer);
}

void SoundManager::setPitch(float timeScale)
{
	for (unsigned i = 0; i < players.size(); i++) {
		players[i].setPitch(timeScale);
	}
}
