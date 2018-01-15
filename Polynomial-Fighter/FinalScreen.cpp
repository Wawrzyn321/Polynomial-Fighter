#include "FinalScreen.h"
#include "AssetManager.h"
#include "Utility.h"
#include "Colors.h"
#include "SoundManager.h"

void FinalScreen::playDrummies()
{ 
	SoundManager::instance()->playSound(Assets::SOUND_FAILED);
}

#pragma region States Update

void FinalScreen::handleScoreState(float lerpAmount)
{
	if (!isFadingIn) return;

	backgroundRectangle.setFillColor(lerp(backgroundRectangle.getFillColor(), Colors::BLACK, lerpAmount));
	backgroundRectangle.setOutlineColor(lerp(backgroundRectangle.getOutlineColor(), Colors::FIRST, lerpAmount));
	gameOverText.setFillColor(lerp(gameOverText.getFillColor(), Colors::SECOND, lerpAmount));
	maliciousText.setFillColor(lerp(maliciousText.getFillColor(), Colors::SECOND, lerpAmount));
	scoreText.setFillColor(lerp(scoreText.getFillColor(), Colors::SECOND, lerpAmount));
	stageText.setFillColor(lerp(stageText.getFillColor(), Colors::SECOND, lerpAmount));
	killedText.setFillColor(lerp(killedText.getFillColor(), Colors::SECOND, lerpAmount));
	pressAnyKeyText.setFillColor(lerp(pressAnyKeyText.getFillColor(), Colors::SECOND, lerpAmount));

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
		pressAnyKeyText.setFillColor(Colors::SECOND);

		stopWatch.OnTime.add(std::bind(&FinalScreen::playDrummies, this));
		stopWatch.reset(400, true);
	}
}

void FinalScreen::handlePromptState(float lerpAmount)
{
	scoreText.setFillColor(lerp(scoreText.getFillColor(), sf::Color::Transparent, lerpAmount));
	stageText.setFillColor(lerp(stageText.getFillColor(), sf::Color::Transparent, lerpAmount));
	killedText.setFillColor(lerp(killedText.getFillColor(), sf::Color::Transparent, lerpAmount));
	pressAnyKeyText.setFillColor(lerp(pressAnyKeyText.getFillColor(), sf::Color::Transparent, lerpAmount));

	pressEnterText.setFillColor(lerp(pressEnterText.getFillColor(), Colors::SECOND, lerpAmount));
	pressEscapeText.setFillColor(lerp(pressEscapeText.getFillColor(), Colors::SECOND, lerpAmount));
}

void FinalScreen::handleFadeoutState(float lerpAmount)
{
	backgroundRectangle.setFillColor(lerp(backgroundRectangle.getFillColor(), sf::Color::Transparent, lerpAmount));
	backgroundRectangle.setOutlineColor(lerp(backgroundRectangle.getOutlineColor(), sf::Color::Transparent, lerpAmount));
	gameOverText.setFillColor(lerp(gameOverText.getFillColor(), sf::Color::Transparent, lerpAmount));
	maliciousText.setFillColor(lerp(maliciousText.getFillColor(), sf::Color::Transparent, lerpAmount));
	scoreText.setFillColor(lerp(scoreText.getFillColor(), sf::Color::Transparent, lerpAmount));
	stageText.setFillColor(lerp(stageText.getFillColor(), sf::Color::Transparent, lerpAmount));
	killedText.setFillColor(lerp(killedText.getFillColor(), sf::Color::Transparent, lerpAmount));
	pressAnyKeyText.setFillColor(lerp(pressAnyKeyText.getFillColor(), sf::Color::Transparent, lerpAmount));
	pressEnterText.setFillColor(lerp(pressEnterText.getFillColor(), Colors::SECOND, lerpAmount));
	pressEscapeText.setFillColor(lerp(pressEscapeText.getFillColor(), Colors::SECOND, lerpAmount));


	if (backgroundRectangle.getFillColor().a < 255-color256Threshold)
	{

	}
}

#pragma endregion

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
	scoreText.setPosition(x*0.5f, y*0.50f);

	stageText = sf::Text("Stage: " + std::to_string(stageNo), *font, unsigned(x * 0.04f));
	centerTextOrigin(stageText);
	stageText.setFillColor(sf::Color::Transparent);
	stageText.setPosition(x*0.5f, y*0.43f);

	killedText = sf::Text("Defeated enemies: " + std::to_string(killedEnemies), *font, unsigned(x * 0.04f));
	centerTextOrigin(killedText);
	killedText.setFillColor(sf::Color::Transparent);
	killedText.setPosition(x*0.5f, y*0.56f);

	pressAnyKeyText = sf::Text("Press any key to continue", *font, unsigned(x * 0.035f));
	centerTextOrigin(pressAnyKeyText);
	pressAnyKeyText.setFillColor(sf::Color::Transparent);
	pressAnyKeyText.setPosition(x*0.5f, y*0.67f);


	pressEnterText = sf::Text("Press 'Return' to play again", *font, unsigned(x * 0.04f));
	centerTextOrigin(pressEnterText);
	pressEnterText.setFillColor(sf::Color::Transparent);
	pressEnterText.setPosition(x*0.5f, y*0.6f);

	pressEscapeText = sf::Text("Press 'Esc' to exit", *font, unsigned(x * 0.04f));
	centerTextOrigin(pressEscapeText);
	pressEscapeText.setFillColor(sf::Color::Transparent);
	pressEscapeText.setPosition(x*0.5f, y*0.67f);
}

FinalScreen::FinalScreen(unsigned score, unsigned killedEnemies, unsigned stageNo)
{
	this->score = score;
	this->killedEnemies = killedEnemies;
	this->stageNo = stageNo + 1;

	state = State::SCORE;
	isFadingIn = true;

	initGraphics();
}

void FinalScreen::update(const Time::TimeData& timeData)
{
	float lerpAmount = timeData.getScaledDeltaTimeInMili() * lerpingSpeed;

	switch (state) {
	case State::SCORE:
		handleScoreState(lerpAmount);
		break;
	case State::PROMPT:
		handlePromptState(lerpAmount);
		break;
	case State::FADEOUT:
		handleFadeoutState(lerpAmount);
		break;
	}

	stopWatch.update(timeData);
}

void FinalScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundRectangle, states);
	target.draw(gameOverText, states);
	target.draw(maliciousText, states);
	if (state == State::SCORE) {
		target.draw(scoreText, states);
		target.draw(stageText, states);
		target.draw(killedText, states);
		target.draw(pressAnyKeyText, states);
	}
	else
	{
		target.draw(pressEnterText, states);
		target.draw(pressEscapeText, states);
	}
}
