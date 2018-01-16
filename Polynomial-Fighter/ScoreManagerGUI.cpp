#include "ScoreManagerGUI.h"
#include "Utility.h"
#include "EntityManager.h"
#include "FleetingText.h"
#include "AssetManager.h"
#include "Colors.h"
#include "HighscoresService.h"

void ScoreManagerGUI::checkHighscores()
{
	if (bestAlreadyBeaten) return;

	if (targetPoints > std::get<0>(minMaxScoresTuple))
	{
		auto v = sf::Vector2f(GameData::WINDOW_SIZE.x*0.82f, GameData::WINDOW_SIZE.y*(-0.1f));
		flashingBestHighscoreText = std::make_unique<FlashingText>("Best highscore!", v, flashingTextsSize);
		flashingBestHighscoreText->setStateValues(v, v + sf::Vector2f(0, GameData::WINDOW_SIZE.y*0.3f));
		flashingBestHighscoreText->state = FlashingText::State::TO_POS_2;
		flashingBestHighscoreText->canFlash = true;
		bestAlreadyBeaten = true;
	}

	if (newAlreadyBeaten) return;

	if (targetPoints > std::get<1>(minMaxScoresTuple))
	{
		auto v = sf::Vector2f(GameData::WINDOW_SIZE.x*0.82f, GameData::WINDOW_SIZE.y*(-0.1f));
		flashingNewHighscoreText = std::make_unique<FlashingText>("New highscore!", v, flashingTextsSize);
		flashingNewHighscoreText->setStateValues(v, v + sf::Vector2f(0, GameData::WINDOW_SIZE.y*0.24f));
		flashingNewHighscoreText->state = FlashingText::State::TO_POS_2;
		flashingNewHighscoreText->canFlash = true;
		newAlreadyBeaten = true;
	}
}

void ScoreManagerGUI::updateStageText(const Time::TimeData& timeData)
{
	switch (stageTextState) {
	case EthericalTextState::DIM:
	{
		float newX = lerp(stageText.getScale().x, 0.0f, timeData.getScaledDeltaTimeInMili()*scalingSpeed);
		stageText.setScale(newX, 1);

		if (abs(newX < stageScalingThreshold))
		{
			stageText.setString(std::to_string(unsigned(stageNo)));
			stageTextState = EthericalTextState::AUG;
		}
	}
	break;
	case EthericalTextState::AUG:
	{
		float newX = lerp(stageText.getScale().x, 1.0f, timeData.getScaledDeltaTimeInMili()*scalingSpeed);
		stageText.setScale(newX, 1);

		if (abs(newX < stageScalingThreshold))

			if (abs(stageText.getScale().x - 1 < stageScalingThreshold))
			{
				stageText.setScale(1, 1);
				stageTextState = EthericalTextState::IDLE;
			}
	}
	break;
	}
}

void ScoreManagerGUI::updateScoreText(const Time::TimeData& timeData)
{
	float scale = scoreText.getScale().x;
	if (abs(scale - 1) > GameData::minScalingThreshold)
	{
		scale = lerp(scale, 1.0f, timeData.getScaledDeltaTimeInMili()*GameData::unscalingSpeed);
		scoreText.setScale(scale, scale);
	}
	else
	{
		scoreText.setScale(1, 1);
	}

	if (targetPoints > currentPoints)
	{
		currentPoints = lerp(currentPoints, float(targetPoints), timeData.getScaledDeltaTimeInMili()*GameData::fillingSpeed);
		if (targetPoints - currentPoints < 1)
		{
			currentPoints = float(targetPoints);
		}
		scoreText.setString("Points: " + std::to_string(unsigned(currentPoints)));
		centerTextOrigin(scoreText);
		scoreText.setPosition(scoreTextPosition);
	}
}

void ScoreManagerGUI::updateFlashingTexts(const Time::TimeData& timeData) const
{
	if (flashingNewHighscoreText)
	{
		flashingNewHighscoreText->update(timeData);
	}
	if (flashingBestHighscoreText)
	{
		flashingBestHighscoreText->update(timeData);
	}
}

void ScoreManagerGUI::initGraphics(const sf::Vector2f& position, const sf::Vector2f& size)
{
	scoreTextPosition = position + sf::Vector2f(size.x*0.5f, size.y*0.333f);
	scoreFontSize = unsigned(size.y*0.6f);

	backgroundRectangle = sf::RectangleShape(size);
	backgroundRectangle.setFillColor(Colors::backgroundColor);
	backgroundRectangle.setOutlineThickness(size.y*0.1f);
	backgroundRectangle.setOutlineColor(Colors::outlineColor);
	backgroundRectangle.setPosition(position);

	font = AssetManager::instance()->getDefaultFont();
	scoreText = sf::Text("Points: 0", *font, scoreFontSize);
	scoreText.setFillColor(Colors::textColor);
	centerTextOrigin(scoreText);
	scoreText.setPosition(scoreTextPosition);

	stageText = sf::Text("1", *font, stageFontSize);
	stageText.setFillColor(lerp(Colors::FOURTH, sf::Color::Transparent, 0.6f));
	sf::FloatRect textRect = stageText.getLocalBounds();
	stageText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	stageText.setPosition(GameData::WINDOW_CENTER);
	stageText.setScale(0, 1);
}

ScoreManagerGUI::ScoreManagerGUI(const sf::Vector2f& position, const sf::Vector2f& size)
{
	currentPoints = 0;
	targetPoints = 0;
	newAlreadyBeaten = false;
	bestAlreadyBeaten = false;

	stageTextState = EthericalTextState::AUG;
	initGraphics(position, size);
	minMaxScoresTuple = HighscoreService::getMinMaxHighscore(true);
}

void ScoreManagerGUI::setTargetPoints(int targetPoints, bool showNotification)
{
	unsigned pointsBefore = targetPoints - this->targetPoints;
	this->targetPoints = static_cast<unsigned int>(targetPoints);
	scoreText.scale(GameData::scaleMultiplier, GameData::scaleMultiplier);

	if (showNotification)
	{
		auto ft = std::make_shared<FleetingText>("+" + std::to_string(pointsBefore),
			scoreTextPosition, Colors::WHITE, scoreFontSize);
		ft->run(0.0009f, { 0, -0.04f }, 0);
		EntityManager::instance()->addEntity(ft);
	}

	checkHighscores();
}

void ScoreManagerGUI::stageFinished(unsigned stageNo)
{
	this->stageNo = stageNo + 1;
	stageTextState = EthericalTextState::DIM;
}

void ScoreManagerGUI::updateScoreToFinal()
{
	currentPoints = float(targetPoints);
}

void ScoreManagerGUI::reset()
{
	currentPoints = 0;
	targetPoints = 0;
	stageNo = 1;
	accumulator = 0;

	scoreText.setString("Points: " + std::to_string(unsigned(currentPoints)));
	centerTextOrigin(scoreText);
	scoreText.setPosition(scoreTextPosition);

	flashingNewHighscoreText.reset();
	flashingBestHighscoreText.reset();
}

void ScoreManagerGUI::update(const Time::TimeData& timeData)
{
	updateStageText(timeData);
	updateScoreText(timeData);
	updateFlashingTexts(timeData);
}

void ScoreManagerGUI::earlyDraw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(stageText, states);
}

void ScoreManagerGUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundRectangle, states);
	target.draw(scoreText, states);
	if (flashingNewHighscoreText)
	{
		target.draw(*flashingNewHighscoreText, states);
	}
	if (flashingBestHighscoreText)
	{
		target.draw(*flashingBestHighscoreText, states);
	}
}

ScoreManagerGUI::~ScoreManagerGUI()
{
	flashingNewHighscoreText.reset();
	flashingBestHighscoreText.reset();
}
