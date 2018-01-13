#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SFML/Audio.hpp>
#include "AssetManager.h"

class SoundManager {
	static SoundManager* sInstance;	

	std::vector<std::shared_ptr<sf::Sound>> players;

	AssetManager *assetManagerInstance = nullptr;

	void play(std::shared_ptr<sf::Sound> sound, std::shared_ptr<sf::SoundBuffer> buffer, const sf::Vector2f& position);

public:
	static SoundManager *instance();

	static float menuSoundShift;
	bool isOn = true;

	void playSound(const std::string& bufferName, const sf::Vector2f &position);

	void playSound(const std::string &bufferName);

	void setPitch(float timeScale);

	void setListenerDirection(float rotation) const;
};

#endif
