#pragma once

#include "player.h"

#include <map>
#include <string>
#include <list>

class LeagueContainer
{
public:
	std::list<Player> searchForPlayers() const;
	void addPlayer();
	void printStatistics();
	void resetLeague() { m_leaguePlayers.clear(); }
	void startNewSeason();
	void saveLeagueToFile();
	void saveSearchToFile(std::list<Player> &searchResult);

private:
	std::map<std::string, Player> m_leaguePlayers;
	int32_t m_currentYear;
};