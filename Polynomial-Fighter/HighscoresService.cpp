#include "HighscoresService.h"
#include <fstream>
#include "AssetManager.h"

std::vector<unsigned> HighscoreService::loadedScores;
bool HighscoreService::scoresAreLoaded = false;

HighscoreService::HighscoreService()
{
}

void HighscoreService::loadHighScores()
{
	loadedScores.clear();
	std::fstream fIn = std::fstream(Assets::PATH_TO_RESOURCES + Assets::PATH_TO_SAVE, std::ios::in);
	if (fIn.good()) {
		unsigned i = 0;
		while (!fIn.eof() && i < maxScoresCount)
		{
			std::string t;
			fIn >> t;

			if (t.empty()) continue;

			try {
				int p = stoi(t);
				loadedScores.push_back(unsigned(p));
			}
			catch (std::invalid_argument&) {}
			i++;
		}
		fIn.close();
	}
	scoresAreLoaded = true;
}

void HighscoreService::saveHighScores()
{
	std::fstream fOut = std::fstream(Assets::PATH_TO_RESOURCES + Assets::PATH_TO_SAVE, std::ios::out);
	for (unsigned score : loadedScores)
	{
		fOut << score << std::endl;
	}
	fOut.close();
}


std::tuple<unsigned, unsigned> HighscoreService::getMinMaxHighscore(bool forceUpdate)
{
	if (!scoresAreLoaded || forceUpdate)
	{
		loadHighScores();
	}
	if (loadedScores.size() == 0)
	{
		return { 0,0 };
	}
	else
	{
		return {
			loadedScores[0],
			loadedScores.back()
		};
	}
}

std::vector<std::string> HighscoreService::getFormattedHighscores(bool forceUpdate)
{
	if (!scoresAreLoaded || forceUpdate)
	{
		loadHighScores();
	}

	std::vector<std::string> v;
	for (unsigned i = 0; i < loadedScores.size(); i++)
	{
		v.push_back(std::to_string(i + 1) + ": " + std::to_string(loadedScores[i]));
	}
	return v;
}

bool HighscoreService::addScore(unsigned score)
{
	if (score == 0)
	{
		return false;
	}
	if (!scoresAreLoaded)
	{
		loadHighScores();
	}

	unsigned i;
	for (i = 0; i < loadedScores.size() && score < loadedScores[i]; i++)
	{
	}
	if (i != maxScoresCount)
	{
		loadedScores.insert(loadedScores.begin() + i, score);
		if (loadedScores.size() > maxScoresCount) {
			loadedScores.resize(maxScoresCount);
		}
		saveHighScores();
		return true;
	}
	return false;
}
