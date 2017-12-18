#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SFML/Audio.hpp>
#include "AssetManager.h"
class PauseManager;

class SoundManager {
private:
	static SoundManager* sInstance;

	std::vector<std::shared_ptr<sf::Sound>> players;

	AssetManager *assetManagerInstance;

	void play(std::shared_ptr<sf::Sound> sound, std::shared_ptr<sf::SoundBuffer> buffer);

public:
	static SoundManager *instance();

	bool isOn = true;

	void playSound(const std::string &bufferName);

	void setPitch(float timeScale);
};

#endif
