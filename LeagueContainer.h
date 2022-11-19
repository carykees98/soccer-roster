#pragma once

#include "Player.h"

#include <map>
#include <string>
#include <list>

class LeagueContainer
{
public:
	std::list<Player> searchForPlayers();
	void addPlayer();
	void printStatistics();
	void resetLeague() { m_leaguePlayers.clear(); }
	void startNewSeason();
	void saveLeagueToFile();
	void saveSearchToFile();

private:
	std::map<std::string, Player> m_leaguePlayers;
	int32_t m_currentYear;
};