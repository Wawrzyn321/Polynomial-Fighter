#include "Asset Manager.h"

AssetManager * AssetManager::sInstance = nullptr;

AssetManager * AssetManager::instance()
{
    if (sInstance == nullptr) {
        sInstance = new AssetManager();
    }

    return sInstance;
}

std::shared_ptr<sf::Texture> AssetManager::getTexture(const std::string &filename)
{
    auto &texMap = sInstance->textures;
    auto pairFound = texMap.find(filename);

    if (pairFound != texMap.end())
	{
		return pairFound->second;
	}
    else
	{
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        
        if (!(*texture).loadFromFile(filename))
		{
			Debug::PrintFormatted("AssetManager::getTexture: cannot load texture %!", filename);

            //WAZNE
            //jak nie zaladuje, to po prostu zwroci pusty asset, przez co program bedzie dalej dzialal bez crasha
            //wedlug mnie to najlepsze rozwiazanie
            //Janusz tez lubil, jak programu nie dalo sie wycrashowac (backslash wiecznie zywy)
        }

        return texture;
    }
}

std::shared_ptr<sf::Font> AssetManager::getFont(const std::string &filename)
{
    auto &sFontMap = sInstance->fonts;
    auto pairFound = sFontMap.find(filename);

	if (pairFound != sFontMap.end())
    {
		return pairFound->second;
	}
    else
    {
        std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();

        if (!(*font).loadFromFile(filename))
        {
			Debug::PrintFormatted("AssetManager::getFont: cannot load font %!", filename);
        }

        return font;
    }
}

std::shared_ptr<sf::SoundBuffer> AssetManager::getSound(const std::string &filename)
{
	auto &sSoundMap = sInstance->sounds;
	auto pairFound = sounds.find(filename);

	if (pairFound != sSoundMap.end())
    {
		return pairFound->second;
	}
	else
    {
        std::shared_ptr<sf::SoundBuffer> sound = std::make_shared<sf::SoundBuffer>();

		if (!(*sound).loadFromFile(filename))
        {
			Debug::PrintFormatted("AssetManager::getSound: cannot load sound %!", filename);
		}

		return sound;
	}
}
