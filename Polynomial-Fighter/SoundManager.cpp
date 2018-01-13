#include "SoundManager.h"
#include "Debug.h"
#include "Utility.h"

SoundManager *SoundManager::sInstance = nullptr;

float SoundManager::menuSoundShift = 0.5f;

void SoundManager::play(std::shared_ptr<sf::Sound> sound, std::shared_ptr<sf::SoundBuffer> buffer, const sf::Vector2f &position)
{
	sound->setPosition({ position.x, 0, position.y });
	sound->setMinDistance(50);
	sound->setBuffer(*buffer);
	sound->play();
}

SoundManager * SoundManager::instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new SoundManager();
        sInstance->assetManagerInstance = AssetManager::instance();
		sInstance->assetManagerInstance->getSound(Assets::SOUND_CLICK);
    }

    return sInstance;
}

void SoundManager::playSound(const std::string &bufferName, const sf::Vector2f &position)
{
	if (!isOn) return;

	auto buffer = assetManagerInstance->getSound(bufferName);
	for (auto &player : players)
	{
		if (player->getStatus() != sf::SoundSource::Status::Playing)
		{
			play(player, buffer, position);
			return;
		}
	}

	std::shared_ptr<sf::Sound> s = std::make_shared<sf::Sound>();
	players.push_back(s);
	play(players.back(), buffer, position);
}

void SoundManager::playSound(const std::string &bufferName)
{
	sf::Vector3f pos = sf::Listener::getPosition();
	playSound(bufferName, {pos.x, pos.z});
}

void SoundManager::setPitch(float timeScale)
{
	for (auto &player : players) {
        player->setPitch(timeScale);
	}
}

void SoundManager::setListenerDirection(float rotation) const
{
	float cs = cosf(rotation * pi / 180.0f);
	float sn = sinf(rotation * pi / 180.0f);
	sf::Listener::setDirection(cs, 0, sn);
}
