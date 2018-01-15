#include "GUIAnimator.h"
#include "TitleText.h"
#include "MainMenu.h"
#include "GUIRing.h"
#include "HighscoresService.h"
#include "HowToImageViewer.h"
#include "AuthorsList.h"
#include "HighscoresList.h"
#include "HowToList.h"
#include "TextsProvider.h"
#include "SoundManager.h"
#include "EasterEgg.h"
#include "FlashingText.h"

void GUIAnimator::initGraphics()
{
	sf::Vector2f size = { float(GameData::WINDOW_SIZE.x) , float(GameData::WINDOW_SIZE.y) };
	sf::Vector2f center = { size.x*0.5f,size.y*0.5f };

	title = new TitleText("Polynomial\n  Fighter", center, unsigned(size.y*0.14f));
	title->setStateValues(center, { center.x, size.y*0.16f });

	ring = new GUIRing(center);

	optionsRing = new GUIRingOptions(center);

	howToViewer = new HowToImageViewer(center + sf::Vector2f(0, size.y*0.05f));
	EasterEgg::setViewer(howToViewer);

	highscores = new HighscoresList(center + sf::Vector2f(0, size.y*0.15f));
	highscores->initTexts(HighscoreService::getFormattedHighscores());

	howTo = new HowToList(center + sf::Vector2f(size.x*0.2f, size.y*0.15f), howToViewer);
	howTo->initTexts(TextsProvider::howTo);

	highscores = new HighscoresList(center + sf::Vector2f(0, size.y*0.15f));
	highscores->initTexts(HighscoreService::getFormattedHighscores());

	authors = new AuthorsList(center + sf::Vector2f(0, size.y*0.15f));
	authors->initTexts(TextsProvider::authors);

	pressAnyKeyText = new FlashingText("Press any key", { size.x*0.5f, size.y*0.9f }, unsigned(size.x*0.04f));
	pressAnyKeyText->state = FlashingText::State::TO_POS_1;
	pressAnyKeyText->setStateValues({ size.x*0.5f, size.y*0.8f }, { size.x*0.5f, size.y*1.1f });
	pressAnyKeyText->canFlash = true;
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
	authors->update(deltaTime);
	pressAnyKeyText->update(timeData);
}

void GUIAnimator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*ring, states);
	target.draw(*title, states);
	target.draw(*optionsRing, states);
	target.draw(*highscores, states);
	target.draw(*howTo, states);
	target.draw(*howToViewer, states);
	target.draw(*authors, states);
	target.draw(*pressAnyKeyText, states);
}

GUIRingOptions::Option GUIAnimator::getRingOption() const
{
	return optionsRing->getCurrentOption();
}

void GUIAnimator::setSplash() const
{
	pressAnyKeyText->text.setFillColor(sf::Color::Transparent);
	pressAnyKeyText->canFlash = false;
	ring->state = GUIRing::State::TO_MINOR;
	title->state = TitleText::State::SPLASH;
	pressAnyKeyText->state = FlashingText::State::TO_POS_1;
	optionsRing->setVisible(false, false);
	SoundManager::instance()->playSound(Assets::SOUND_MENU_BACK);
}

void GUIAnimator::setMenu(bool resetCurrentOption, bool playSound) const
{
	SoundManager::instance()->setListenerDirection(0);
	ring->state = GUIRing::State::TO_MAJOR;
	title->state = TitleText::State::MENU;
	pressAnyKeyText->state = FlashingText::State::TO_POS_2;
	optionsRing->setVisible(true, resetCurrentOption);
	optionsRing->isTransitioningToGame = false;
	howToViewer->hideAll();
	if (playSound) {
		SoundManager::instance()->playSound(Assets::SOUND_CLICK);
	}
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

void GUIAnimator::setToGame() const
{
	title->state = TitleText::State::UP;
	ring->state = GUIRing::State::TO_GAME;
	optionsRing->isTransitioningToGame = true;
}

void GUIAnimator::rotateRingRight() const
{
	optionsRing->switchRight();
}

void GUIAnimator::rotateRingLeft() const
{
	optionsRing->switchLeft();
}

void GUIAnimator::moveHighscoresUp() const
{
	highscores->moveUp();
}

void GUIAnimator::moveHighscoresDown() const
{
	highscores->moveDown();
}

void GUIAnimator::setHighscoresVisibles(bool visible) const{
	if (visible)
	{
		highscores->initTexts(HighscoreService::getFormattedHighscores());
		ring->state = GUIRing::State::TO_MEDIUM;
	}
	optionsRing->isZoomed = visible;
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
	if (visible)
	{
		ring->state = GUIRing::State::TO_RIGHT_MEDIUM;
		howToViewer->show(0);

		if (EasterEgg::hasAlreadyDoneThat) {
			auto texts = TextsProvider::howTo;
			texts.back() = "Get lost.";
			howTo->initTexts(texts);
		}
	}

	optionsRing->isZoomed = visible;
	howTo->setVisible(visible);
}

void GUIAnimator::moveAuthorsUp() const
{
	authors->moveUp();
}

void GUIAnimator::moveAuthorsDown() const
{
	authors->moveDown();
}

void GUIAnimator::setAuthorsVisible(bool visible) const {
	if (visible) {
		ring->state = GUIRing::State::TO_MEDIUM;

		if (EasterEgg::hasAlreadyDoneThat) {
			auto texts = TextsProvider::authors;
			std::string t = texts.back();
			texts.back() = t.substr(0, t.size() - 4) + "Xulk";
			authors->initTexts(texts);
		}
	}
	optionsRing->isZoomed = visible;
	authors->setVisible(visible);
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
	delete authors;
	delete pressAnyKeyText;
}
