#include "FinalScreen.h"
#include "AssetManager.h"
#include "Utility.h"
#include "Colors.h"
#include "SoundManager.h"

void FinalScreen::playDrummies()
{ 
	SoundManager::instance()->playSound(Assets::SOUND_FAILED);
}

void FinalScreen::initGraphics()
{
	float x = float(GameData::WINDOW_SIZE.x);
	float y = float(GameData::WINDOW_SIZE.y);
	font = AssetManager::instance()->getDefaultFont();

	backgroundRectangle.setSize({ x*0.5f, y*0.5f });
	backgroundRectangle.setFillColor(sf::Color::Transparent);
	backgroundRectangle.setOutlineColor(sf::Color::Transparent);
	backgroundRectangle.setOrigin(x*0.25f, y*0.25f);
	backgroundRectangle.setOutlineThickness(x*0.005f);
	backgroundRectangle.setPosition(x*0.5f, y*0.5f);

	gameOverText = sf::Text("Game over", *font, unsigned(x * 0.05f));
	centerTextOrigin(gameOverText);
	gameOverText.setFillColor(sf::Color::Transparent);
	gameOverText.setPosition(x*0.5f, y*0.27f);

	maliciousText = sf::Text("It was your game, but now it's over.", *font, unsigned(x * 0.025f));
	centerTextOrigin(maliciousText);
	maliciousText.setFillColor(sf::Color::Transparent);
	maliciousText.setPosition(x*0.5f, y*0.34f);

	scoreText = sf::Text("Score: " + std::to_string(score) + " points", *font, unsigned(x * 0.04f));
	centerTextOrigin(scoreText);
	scoreText.setFillColor(sf::Color::Transparent);
	scoreText.setPosition(x*0.5f, y*0.52f);

	stageText = sf::Text("Stage: " + std::to_string(stageNo), *font, unsigned(x * 0.04f));
	centerTextOrigin(stageText);
	stageText.setFillColor(sf::Color::Transparent);
	stageText.setPosition(x*0.5f, y*0.45f);

	killedText = sf::Text("Defeated enemies: " + std::to_string(killedEnemies), *font, unsigned(x * 0.04f));
	centerTextOrigin(killedText);
	killedText.setFillColor(sf::Color::Transparent);
	killedText.setPosition(x*0.5f, y*0.59f);

	whatExitText = sf::Text("Press 'Esc' to exit", *font, unsigned(x * 0.035f));
	centerTextOrigin(whatExitText);
	whatExitText.setFillColor(sf::Color::Transparent);
	whatExitText.setPosition(x*0.5f, y*0.7f);
}

FinalScreen::FinalScreen(unsigned score, unsigned killedEnemies, unsigned stageNo)
{
	this->score = score;
	this->killedEnemies = killedEnemies;
	this->stageNo = stageNo + 1;

	isFadingIn = true;

	initGraphics();
}

void FinalScreen::update(const Time::TimeData& timeData)
{
	if (isFadingIn)
	{
		float deltaTime = timeData.getScaledDeltaTimeInMili();
		backgroundRectangle.setFillColor(lerp(backgroundRectangle.getFillColor(), Colors::BLACK, deltaTime * lerpingSpeed));
		backgroundRectangle.setOutlineColor(lerp(backgroundRectangle.getOutlineColor(), Colors::FIRST, deltaTime * lerpingSpeed));
		gameOverText.setFillColor(lerp(gameOverText.getFillColor(), Colors::SECOND, deltaTime * lerpingSpeed));
		maliciousText.setFillColor(lerp(maliciousText.getFillColor(), Colors::SECOND, deltaTime * lerpingSpeed));
		scoreText.setFillColor(lerp(scoreText.getFillColor(), Colors::SECOND, deltaTime * lerpingSpeed));
		stageText.setFillColor(lerp(stageText.getFillColor(), Colors::SECOND, deltaTime * lerpingSpeed));
		killedText.setFillColor(lerp(killedText.getFillColor(), Colors::SECOND, deltaTime * lerpingSpeed));
		whatExitText.setFillColor(lerp(whatExitText.getFillColor(), Colors::SECOND, deltaTime * lerpingSpeed));

		if (backgroundRectangle.getFillColor().a > color256Threshold)
		{
			isFadingIn = false;

			backgroundRectangle.setFillColor(Colors::BLACK);
			backgroundRectangle.setOutlineColor(Colors::FIRST);
			gameOverText.setFillColor(Colors::SECOND);
			maliciousText.setFillColor(Colors::SECOND);
			scoreText.setFillColor(Colors::SECOND);
			stageText.setFillColor(Colors::SECOND);
			killedText.setFillColor(Colors::SECOND);
			whatExitText.setFillColor(Colors::SECOND);

			stopWatch.OnTime.add(std::bind(&FinalScreen::playDrummies, this));
			stopWatch.reset(400, true);
		}
	}

	stopWatch.update(timeData);
}

void FinalScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundRectangle, states);
	target.draw(gameOverText, states);
	target.draw(maliciousText, states);
	target.draw(scoreText, states);
	target.draw(stageText, states);
	target.draw(killedText, states);
	target.draw(whatExitText, states);
}
