#include "GUIAnimator.h"
#include "TitleText.h"
#include "MainMenu.h"
#include "GUIRing.h"
#include "HelpProvider.h"
#include "HighscoresService.h"
#include "HowToImageViewer.h"

void GUIAnimator::initGraphics()
{
	sf::Vector2f size = { float(GameData::WINDOW_SIZE.x) , float(GameData::WINDOW_SIZE.y) };
	sf::Vector2f center = { size.x*0.5f,size.y*0.5f };

	title = new TitleText("Polynomial\n    Fighter", center, unsigned(size.y*0.14f));
	title->setStateValues(center, { center.x, size.y*0.16f });

	ring = new GUIRing(center);

	optionsRing = new GUIRingOptions(center);

	howToViewer = new HowToImageViewer(center);

	highscores = new HighscoresGUI(center + sf::Vector2f(0, size.x*0.11f));
	highscores->initTexts(HighscoreService::getFormattedHighscores());

	howTo = new HowToGUI(center + sf::Vector2f(size.x*0.2f, size.y*0.05f), howToViewer);
	howTo->initTexts(std::vector<std::string>(HelpProvider::texts, HelpProvider::texts + HelpProvider::len));
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
	howToViewer->update(deltaTime);
}

void GUIAnimator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*ring, states);
	target.draw(*title, states);
	target.draw(*optionsRing, states);
	target.draw(*highscores, states);
	target.draw(*howTo, states);
	target.draw(*howToViewer, states);
}

GUIRingOptions::Option GUIAnimator::getRingOption() const
{
	return optionsRing->getCurrentOption();
}

void GUIAnimator::setSplash() const
{
	ring->state = GUIRing::State::TO_MINOR;
	title->state = TitleText::State::SPLASH;
	optionsRing->setVisible(false, false);
}

void GUIAnimator::setMenu(bool resetCurrentOption) const
{
	ring->state = GUIRing::State::TO_MAJOR;
	title->state = TitleText::State::MENU;
	optionsRing->setVisible(true, resetCurrentOption);
	optionsRing->isToGame = false;
	howToViewer->hideAll();
}

void GUIAnimator::setEmptyCenter() const
{
	ring->state = GUIRing::State::TO_MINOR;
	title->state = TitleText::State::UP;
	optionsRing->setVisible(false, false);
}

void GUIAnimator::setExiting() const
{
	title->state = TitleText::State::EXITING;
	ring->state = GUIRing::State::EXITING;
	optionsRing->setExiting();
}

void GUIAnimator::setToGame()
{
	title->state = TitleText::State::UP;
	ring->state = GUIRing::State::TO_GAME;
	optionsRing->isToGame = true;
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
	if(visible){
		highscores->initTexts(HighscoreService::getFormattedHighscores());
		ring->state = GUIRing::State::TO_MEDIUM;
	}
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
	if(visible){
		ring->state = GUIRing::State::TO_RIGHT_MEDIUM;
		howToViewer->show(0);
	}
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
	delete howToViewer;
}
