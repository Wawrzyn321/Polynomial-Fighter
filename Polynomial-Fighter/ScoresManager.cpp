#include "ScoresManager.h"

ScoresManager::ScoresManager(unsigned capacity)
{
	guiSet = false;
	scores.clear();
	scores = std::vector<int>(capacity, 0);
}

void ScoresManager::setGUI(sf::Vector2f position, float scale)
{
	gui = ScoreManagerGUI(position, (unsigned)scores.size(), scale);
	guiSet = true;
	gui.updateScores(scores);
}

void ScoresManager::loadScores(std::vector<int> v)
{
	scores = std::vector<int>(v);
	if (guiSet) {
		gui.updateScores(scores);
	}
}

bool ScoresManager::loadScores(std::string path) {

	std::fstream fileIn(path, std::ios::in);
	if (fileIn.bad()) {
		std::cout << "ScoresManager: Failed to load scores! (" << path << ")" << std::endl;
		return false;
	}

	unsigned i = 0;
	while (!fileIn.eof() && i < scores.size()) {
		fileIn >> scores[i];
		i++;
	}

	if (guiSet) {
		gui.updateScores(scores);
	}
	fileIn.close();
	return true;
}

bool ScoresManager::saveScores(std::string path)
{
	if (scores.size() == 0) {
		std::cout << "ScoresManager: No scores to save!" << std::endl;
		return false;
	}
	std::fstream fileOut(path, std::ios::out | std::ios::trunc);
	if (fileOut.bad()) {
		std::cout << "ScoresManager: Failed to save scores! (" << path << ")" << std::endl;
		return false;
	}
	for (unsigned i = 0; i < scores.size(); i++) {
		fileOut << scores[i];// >> std::endl;
		fileOut << toString('\n');
	}
	fileOut.close();
	return true;
}

void ScoresManager::addScore(int value) {
	int pos = 0;
	while (scores[pos] > value && pos < scores.size()) {
		pos++;
	}
	scores.insert(scores.begin() + pos, value);
	scores.resize(scores.size() - 1);

	if (guiSet) {
		gui.updateScores(scores);
	}
}

void ScoresManager::drawGUI(sf::RenderTarget& target, sf::RenderStates states) {
	target.draw(gui, states);
}

void ScoresManager::clearScores(std::string path)
{
	std::ofstream fileOut;
	fileOut.open(path, std::ofstream::out | std::ofstream::trunc);
	fileOut.close();
	for (unsigned i = 0; i < scores.size(); i++){
		scores[i] = 0;
	}
	if (guiSet) {
		gui.updateScores(scores);
	}
}
