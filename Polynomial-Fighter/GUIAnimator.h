#ifndef GUI_ANIMATOR_H
#define GUI_ANIMATOR_H
#include "Timer.h"
#include "GUIRingOptions.h"

class MainMenu;
class GUIRing;
class TitleText;
class HowToImageViewer;
class AuthorsList;
class HighscoresList;
class HowToList;
class GUIAnimator
{
	GUIRing *ring;
	TitleText *title;
	GUIRingOptions *optionsRing;
	MainMenu* menuReference;
	HowToImageViewer* howToViewer;

	HighscoresList *highscores;
	HowToList *howTo;
	AuthorsList *authors;

	void initGraphics();
public:
	GUIAnimator(MainMenu *menuReference);

	void update(const Time::TimeData& timeData) const;

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

	GUIRingOptions::Option getRingOption() const;

	void setSplash() const;

	void setMenu(bool resetCurrentOption, bool playSound = true) const;

	void setEmptyCenter() const;

	void setExiting() const;

	void setToGame() const;

	void rotateRingLeft() const;

	void rotateRingRight() const;

	void moveHighscoresUp() const;

	void moveHighscoresDown() const;

	void setHighscoresVisibles(bool visible) const;

	void moveHowToUp() const;

	void moveHowToDown() const;

	void setHowToVisible(bool visible) const;

	void moveAuthorsUp() const;

	void moveAuthorsDown() const;

	void setAuthorsVisible(bool visible) const;

	void setSound(bool isOn) const;

	~GUIAnimator();
};

#endif