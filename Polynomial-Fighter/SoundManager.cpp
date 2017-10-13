#include "SoundManager.h"

using namespace std;

SoundManager *SoundManager::sInstance = nullptr;

void SoundManager::play(std::shared_ptr<sf::Sound> sound, std::shared_ptr<sf::SoundBuffer> buffer)
{
	sound->setBuffer(*buffer);
	sound->play();
}

SoundManager * SoundManager::instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new SoundManager();
        sInstance->assetManagerInstance = AssetManager::instance();
    }

    return sInstance;
}

void SoundManager::playSound(const std::string &bufferName)
{
	if (!isOn) return;

	auto buffer = assetManagerInstance->getSound(bufferName);

	for (auto &player : players)
	{
		if ((*player).getStatus() != sf::SoundSource::Status::Playing)
		{
			play(player, buffer);
			return;
		}
	}

	std::shared_ptr<sf::Sound> s = std::make_shared<sf::Sound>();
	players.push_back(s);
	play(players.back(), buffer);
}

void SoundManager::setPitch(float timeScale)
{
	for (auto &player : players) {
        (*player).setPitch(timeScale);
	}
}
