#include "ScoreManagerGUI.h"
#include "Utility.h"
#include "EntityManager.h"
#include "FleetingText.h"
#include "AssetManager.h"
#include "Colors.h"

void ScoreManagerGUI::updateScoreText()
{
	scoreText.setString(std::to_string(stageNo) + " / " + std::to_string(unsigned(currentPoints)));
	centerTextOrigin(scoreText);
	scoreText.setPosition(textPosition);
}

void ScoreManagerGUI::initGraphics(const sf::Vector2f& position, const sf::Vector2f& size)
{
	textPosition = position + sf::Vector2f(size.x*0.5f, size.y*0.333f);
	fontSize = unsigned(size.y*0.6f);

	backgroundRectangle = sf::RectangleShape(size);
	backgroundRectangle.setFillColor(Colors::backgroundColor);
	backgroundRectangle.setOutlineThickness(size.y*0.1f);
	backgroundRectangle.setOutlineColor(Colors::outlineColor);
	backgroundRectangle.setPosition(position);

	font = AssetManager::instance()->getDefaultFont();
	scoreText = sf::Text("1/0", *font, fontSize);
	scoreText.setFillColor(Colors::textColor);
	centerTextOrigin(scoreText);
	scoreText.setPosition(textPosition);
}

ScoreManagerGUI::ScoreManagerGUI(const sf::Vector2f& position, const sf::Vector2f& size)
{
	currentPoints = 0;
	targetPoints = 0;

	initGraphics(position, size);
}

void ScoreManagerGUI::setTargetPoints(int targetPoints)
{
	this->targetPoints = static_cast<unsigned int>(targetPoints);
	scoreText.scale(scaleMultiplier, scaleMultiplier);
}

void ScoreManagerGUI::updateStageNo(unsigned stageNo, unsigned pointsToAdd)
{
	this->stageNo = stageNo;

	if (pointsToAdd > 0)
	{
		targetPoints += pointsToAdd;
		auto ft = std::make_shared<FleetingText>("+" + std::to_string(pointsToAdd), 
			textPosition, Colors::WHITE, fontSize);
		ft->run(0.0009f, { 0, -0.04f }, 0);
		EntityManager::instance()->addEntity(ft);
	}

	updateScoreText();
}

void ScoreManagerGUI::showFinalScore()
{
	currentPoints = float(targetPoints);
}

void ScoreManagerGUI::reset()
{
	currentPoints = 0;
	targetPoints = 0;
	stageNo = 1;
	accumulator = 0;
	updateStageNo(stageNo);
}

void ScoreManagerGUI::update(const Time::TimeData& timeData)
{
	float scale = scoreText.getScale().x;
	if (abs(scale - 1) > minScalingThreshold)
	{
		scale = lerp(scale, 1.0f, timeData.getScaledDeltaTimeInMili()*unscalingSpeed);
		scoreText.setScale(scale, scale);
	}
	else
	{
		scoreText.setScale(1, 1);
	}

	if (targetPoints > currentPoints)
	{
		currentPoints = lerp(currentPoints, float(targetPoints), timeData.getScaledDeltaTimeInMili()*fillingSpeed);
		if (targetPoints - currentPoints < 1)
		{
			currentPoints = float(targetPoints);
		}

		updateScoreText();
	}
}

void ScoreManagerGUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundRectangle, states);
	target.draw(scoreText, states);
}
