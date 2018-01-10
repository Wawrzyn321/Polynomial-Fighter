#ifndef GUI_ANIMATOR_H
#define GUI_ANIMATOR_H
#include "Timer.h"
#include "GUIRingOptions.h"
#include "HighscoresGUI.h"
#include "HowToGUI.h"

class MainMenu;
class GUIRing;
class TitleText;
class GUIAnimator
{
	GUIRing *ring;
	TitleText *title;
	GUIRingOptions *optionsRing;
	MainMenu* menuReference;
	HighscoresGUI *highscores;
	HowToGUI *howTo;

	void initGraphics();
public:
	GUIAnimator(MainMenu *menuReference);

	void update(const Time::TimeData& timeData) const;

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

	GUIRingOptions::Option getRingOption() const;

	void setSplash() const;

	void setMenu(bool resetCurrentOption) const;

	void setEmptyCenter() const;

	void setExiting() const;

	void setToGame();

	void rotateRingLeft() const;

	void rotateRingRight() const;

	void moveHighscoresUp() const;

	void moveHighscoresDown() const;

	void setHighscoresVisible(bool visible) const;

	void moveHowToUp() const;

	void moveHowToDown() const;

	void setHowToVisible(bool visible) const;

	void setSound(bool isOn) const;

	~GUIAnimator();
};

#endif