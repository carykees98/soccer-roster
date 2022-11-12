#include "LeagueContainer.h"

#include <list>

std::list<Player> LeagueContainer::findPlayerByLast(std::string lastName)
{
	std::list<Player> matchedPlayers;
	for (auto player : m_leaguePlayers)
	{
		if (player.second.getLast() == lastName)
		{
			matchedPlayers.push_back(player.second);
		}
	}
	return matchedPlayers;
}