#pragma once

#include "player.h"

#include <map>
#include <string>
#include <list>
#include <utility>

class LeagueContainer
{
public:
	// Accessors
	int currentYear() const { return m_currentYear; }

	// Search Related
	std::list<std::pair<std::string, Player>> searchForPlayers(bool &foundMatches) const;
	void saveLeagueToFile();
	void saveSearchToFile(std::list<std::pair<std::string, Player>> &searchResult);

	// Uncategorized
	void addPlayer(std::string &errorMessage);
	void printStatistics();
	void resetLeague() { m_leaguePlayers.clear(); }
	void startNewSeason();
	void update(std::list<std::pair<std::string, Player>> &searchResult);

private:
	std::map<std::string, Player> m_leaguePlayers;
	int m_currentYear;
};