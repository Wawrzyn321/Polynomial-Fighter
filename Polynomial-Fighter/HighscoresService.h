#ifndef HIGHSCORE_SERVICE_H
#define HIGHSCORE_SERVICE_H
#include <vector>
#include "GameData.h"

class HighscoreService
{
	HighscoreService();
	static bool scoresAreLoaded;
	static std::vector<unsigned> loadedScores;
	static const unsigned maxScoresCount = 10;

	static void loadHighScores();

	static void saveHighScores();
public:

	static std::vector<std::string> getFormattedHighscores();

	static bool addScore(unsigned score);
};

#endif