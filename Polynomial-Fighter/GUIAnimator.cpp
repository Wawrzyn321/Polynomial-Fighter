#include "GUIAnimator.h"
#include "TitleText.h"
#include "MainMenu.h"
#include "GUIRing.h"

void GUIAnimator::initGraphics()
{
	sf::Vector2f center = {
		GameData::WINDOW_SIZE.x*0.5f,
		GameData::WINDOW_SIZE.y*0.5f,
	};
	title = new TitleText("Polynomial\n    Fighter", center, unsigned(GameData::WINDOW_SIZE.y*0.14f));
	title->setStateValues(center, { center.x, GameData::WINDOW_SIZE.y*0.16f });

	ring = new GUIRing(center);
	optionsRing = new GUIRingOptions(center);
	highscores = new HighscoresGUI(center);
	howTo = new HowToGUI(center);
}

GUIAnimator::GUIAnimator(MainMenu* menuReference)
{
	this->menuReference = menuReference;

	initGraphics();
}

void GUIAnimator::update(const Time::TimeData& timeData) const
{
	float deltaTime = timeData.getScaledDeltaTimeInMili();

	ring->update(deltaTime);
	title->update(deltaTime);
	optionsRing->update(deltaTime);
	highscores->update(deltaTime);
	howTo->update(deltaTime);
}

void GUIAnimator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*ring, states);
	target.draw(*title, states);
	target.draw(*optionsRing, states);
	target.draw(*highscores, states);
	target.draw(*howTo, states);
}

GUIRingOptions::Option GUIAnimator::getRingOption() const
{
	return optionsRing->getCurrentOption();
}

void GUIAnimator::setSplash() const
{
	ring->state = GUIRing::State::TO_MINOR;
	title->state = TitleText::TripleState::MENU;
	optionsRing->setVisible(false, false);
}

void GUIAnimator::setMenu(bool resetCurrentOption) const
{
	ring->state = GUIRing::State::TO_MAJOR;
	title->state = TitleText::TripleState::SPLASH;
	optionsRing->setVisible(true, resetCurrentOption);
}

void GUIAnimator::setEmptyCenter() const
{
	ring->state = GUIRing::State::TO_MINOR;
	title->state = TitleText::TripleState::UP;
	optionsRing->setVisible(false, false);
}

void GUIAnimator::setExiting() const
{
	optionsRing->setExiting();
	title->state = TitleText::TripleState::EXITING;
	ring->state = GUIRing::State::EXITING;
}

void GUIAnimator::rotateRingLeft() const
{
	optionsRing->switchLeft();
}

void GUIAnimator::rotateRingRight() const
{
	optionsRing->switchRight();
}

void GUIAnimator::moveHighscoresUp() const
{
	highscores->moveUp();
}

void GUIAnimator::moveHighscoresDown() const
{
	highscores->moveDown();
}

void GUIAnimator::setHighscoresVisible(bool visible) const{
	highscores->setVisible(visible);
}

void GUIAnimator::moveHowToUp() const
{
	howTo->moveUp();
}

void GUIAnimator::moveHowToDown() const
{
	howTo->moveDown();
}

void GUIAnimator::setHowToVisible(bool visible) const {
	howTo->setVisible(visible);
}

void GUIAnimator::setSound(bool isOn) const
{
	optionsRing->setSoundOn(isOn);
}

GUIAnimator::~GUIAnimator()
{
	delete ring;
	delete title;
	delete optionsRing;
	delete highscores;
	delete howTo;
}

