#pragma once

#include "Player.h"

#include <map>
#include <string>
#include <list>

class LeagueContainer
{
public:
	void loadFromFile();
	void saveToFile();
	std::list<Player> findPlayerByLast(std::string lastName);

private:
	std::map<std::string, Player> m_leaguePlayers;
};