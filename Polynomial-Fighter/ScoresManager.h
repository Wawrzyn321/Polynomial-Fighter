#ifndef SCORESMANAGER_H
#define SCORESMANAGER_H

#include "ScoresManagerGUI.h"

#include <fstream>

class ScoresManager {
private:
	std::vector<int> scores;
	ScoreManagerGUI gui;

	bool guiSet = false;
public:
	ScoresManager() = default;
	ScoresManager(unsigned int capacity);

	void setGUI(sf::Vector2f position, float scale);

	void loadScores(const std::vector<int> &v);

	bool loadScores(std::string path);

	bool saveScores(std::string path);

	void addScore(int value);

	void drawGUI(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

	void clearScores(std::string path);
};


#endif