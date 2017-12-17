#include "AssetManager.h"
#include "Debug.h"

AssetManager * AssetManager::sInstance = nullptr;

AssetManager * AssetManager::instance()
{
    if (sInstance == nullptr)
    {
        sInstance = new AssetManager();
    }

    return sInstance;
}

AssetManager::TexturePointer AssetManager::getTexture(const std::string &filename)
{
    auto pairFound = textures.find(filename);

    if (pairFound != textures.end())
    {
        return pairFound->second;
    }
    else
    {
        TexturePointer texture = std::make_shared<sf::Texture>();

        if (!texture->loadFromFile(GameData::PATH_TO_RESOURCES + GameData::PATH_TO_IMAGES + filename))
        {
            Debug::PrintFormatted("AssetManager::getTexture: cannot load texture %!", filename);
        }
        else
        {
            textures[filename] = std::move(texture);
        }

        return texture;
    }
}

AssetManager::FontPointer AssetManager::getFont(const std::string &filename)
{
    auto pairFound = fonts.find(filename);

    if (pairFound != fonts.end())
    {
        return pairFound->second;
    }
    else
    {
        FontPointer font = std::make_shared<sf::Font>();

        if (!font->loadFromFile(GameData::PATH_TO_RESOURCES + GameData::PATH_TO_FONTS + filename))
        {
            Debug::PrintFormatted("AssetManager::getFont: cannot load font %!", filename);
        }
        else
        {
            fonts[filename] = std::move(font);
        }

        return font;
    }
}

AssetManager::SoundBufferPointer AssetManager::getSound(const std::string &filename)
{
    auto pairFound = sounds.find(filename);

    if (pairFound != sounds.end())
    {
        return pairFound->second;
    }
    else
    {
        SoundBufferPointer soundBuffer = std::make_shared<sf::SoundBuffer>();

        if (!soundBuffer->loadFromFile(GameData::PATH_TO_RESOURCES + GameData::PATH_TO_SOUNDS + filename))
        {
            Debug::PrintFormatted("AssetManager::getSound: cannot load sound %!", filename);
        }
        else
        {
            sounds[filename] = std::move(soundBuffer);
        }

        return soundBuffer;
    }
}

AssetManager::FontPointer AssetManager::getDefaultFont()
{
    return getFont(GameData::FONT_REGULAR);
}