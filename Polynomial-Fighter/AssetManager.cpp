#include "AssetManager.h"
#include "Debug.h"

const std::string Assets::FONT_REGULAR = "Aleo-Regular.otf";
const std::string Assets::FONT_ITALIC = "Aleo-Italic.otf";
const std::string Assets::FONT_MONOSPACE = "monofonto.ttf";

const std::string Assets::PATH_TO_RESOURCES = "res/";
const std::string Assets::PATH_TO_IMAGES = "img/";
const std::string Assets::PATH_TO_HOW_TO = "howto/";
const std::string Assets::PATH_TO_FONTS = "fonts/";
const std::string Assets::PATH_TO_SOUNDS = "sounds/";
const std::string Assets::PATH_TO_SAVE = "save.dat";
const std::string Assets::PATH_TO_COLOR_SCHEME = "colorScheme.dat";

const std::string Assets::ICON = "icon.png";

const std::string Assets::SOUND_ADD_ROUNDS = "add_rounds.ogg";
const std::string Assets::SOUND_DIV_0 = "div0.ogg";
const std::string Assets::SOUND_ENEMY_HIT = "enemy_hit_0X.ogg";
const unsigned Assets::SOUND_ENEMY_HIT_REPLACE = 11;
const std::string Assets::SOUND_ENEMY_SHOOT = "enemy_shoot_0X.ogg";
const unsigned Assets::SOUND_ENEMY_SHOOT_REPLACE = 13;
const std::string Assets::SOUND_FAILED = "failed.ogg"; //todo
const std::string Assets::SOUND_MENU_BACK = "menu_back.ogg";
const std::string Assets::SOUND_CLICK = "menu_click.ogg";
const std::string Assets::SOUND_EXIT = "menu_exit.ogg";
const std::string Assets::SOUND_NO_ROUNDS = "no_rounds.ogg";
const std::string Assets::SOUND_PAUSE = "pause.ogg";
const std::string Assets::SOUND_PLAYER_HIT = "player_hit_0X.ogg";
const int Assets::SOUND_PLAYER_HIT_REPLACE = 12;
const std::string Assets::SOUND_PLAYER_SHOOT = "player_shoot.ogg";
const std::string Assets::SOUND_SOUND_ON = "sound_on.ogg";
const std::string Assets::SOUND_WAVE = "wave.ogg";
const std::string Assets::SOUND_EXPLOSION_LONG = "explosion_long.ogg";
const std::string Assets::SOUND_EXPLOSION_SHORT = "explosion_short.ogg";
const std::string Assets::SOUND_GAME_LOAD = "game_load.ogg";
const std::string Assets::SOUND_ROLLING_LIST_MOVE = "rolling_list_move.ogg";
const std::string Assets::SOUND_MISS = "miss.ogg";

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

        if (!texture->loadFromFile(Assets::PATH_TO_RESOURCES + Assets::PATH_TO_IMAGES + filename))
        {
            Debug::PrintFormatted("AssetManager::getTexture: cannot load texture %!", filename);
            return texture;
        }
        else
        {
            textures[filename] = std::move(texture);
            return textures[filename];
        }
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

        if (!font->loadFromFile(Assets::PATH_TO_RESOURCES + Assets::PATH_TO_FONTS + filename))
        {
            Debug::PrintFormatted("AssetManager::getFont: cannot load font %!", filename);
            return font;
        }
        else
        {
            fonts[filename] = std::move(font);
            return fonts[filename];
        }
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

        if (!soundBuffer->loadFromFile(Assets::PATH_TO_RESOURCES + Assets::PATH_TO_SOUNDS + filename))
        {
            Debug::PrintFormatted("AssetManager::getSound: cannot load sound %!", filename);
            return soundBuffer;
        }
        else
        {
            sounds[filename] = std::move(soundBuffer);
            return sounds[filename];
        }
    }
}

AssetManager::FontPointer AssetManager::getDefaultFont()
{
    return getFont(Assets::FONT_REGULAR);
}