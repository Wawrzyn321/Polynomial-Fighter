#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SFML\Audio.hpp>
#include "Asset Manager.h"
class PauseManager;

class SoundManager {
	friend class PauseManager;
private:
	SoundManager() {}
	static SoundManager* sInstance;

	std::vector<sf::Sound> players;

	AssetManager *assetManagerInstance;

	void play(sf::Sound * sound, sf::SoundBuffer *buffer);

	void setPitch(float timeScale);
public:
	static SoundManager *instance();

	bool isOn = true;

	void playSound(std::string bufferName);

};

#endif
