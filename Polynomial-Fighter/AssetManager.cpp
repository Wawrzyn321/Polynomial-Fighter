#include "Asset Manager.h"
#include "Debug.h"

AssetManager * AssetManager::sInstance = nullptr;

AssetManager * AssetManager::instance()
{
    if (sInstance == nullptr) {
        sInstance = new AssetManager();
    }

    return sInstance;
}

AssetManager::TexturePointer AssetManager::getTexture(const std::string &filename)
{
    auto &texMap = sInstance->textures;
    auto pairFound = texMap.find(filename);

    if (pairFound != texMap.end())
	{
		return pairFound->second;
	}
    else
	{
		TexturePointer texture = std::make_shared<sf::Texture>();
        
        if (!texture->loadFromFile(filename))
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

AssetManager::FontPointer AssetManager::getFont(const std::string &filename)
{
    auto &sFontMap = sInstance->fonts;
    auto pairFound = sFontMap.find(filename);

	if (pairFound != sFontMap.end())
    {
		return pairFound->second;
	}
    else
    {
		FontPointer font = std::make_shared<sf::Font>();

        if (!font->loadFromFile(filename))
        {
			Debug::PrintFormatted("AssetManager::getFont: cannot load font %!", filename);
        }

        return font;
    }
}

AssetManager::SoundBufferPointer AssetManager::getSound(const std::string &filename)
{
	auto &sSoundMap = sInstance->sounds;
	auto pairFound = sounds.find(filename);

	if (pairFound != sSoundMap.end())
    {
		return pairFound->second;
	}
	else
    {
		SoundBufferPointer sound = std::make_shared<sf::SoundBuffer>();

		if (!sound->loadFromFile(filename))
        {
			Debug::PrintFormatted("AssetManager::getSound: cannot load sound %!", filename);
		}

		return sound;
	}
}

AssetManager::FontPointer AssetManager::getDefaultFont()
{
	return getFont(GameData::PATH_TO_RESOURCES + GameData::PATH_TO_FONTS + GameData::FONT_REGULAR);
}
