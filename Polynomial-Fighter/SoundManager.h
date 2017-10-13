#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SFML/Audio.hpp>
#include "Asset Manager.h"
class PauseManager;

class SoundManager {
	friend class PauseManager;
private:
	static SoundManager* sInstance;

	std::vector<std::shared_ptr<sf::Sound>> players;

	AssetManager *assetManagerInstance;

	void play(std::shared_ptr<sf::Sound> sound, std::shared_ptr<sf::SoundBuffer> buffer);

	void setPitch(float timeScale);
public:
	static SoundManager *instance();

	bool isOn = true;

	void playSound(const std::string &bufferName);
};

#endif
