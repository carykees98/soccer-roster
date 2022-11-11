#pragma once

#include "Player.h"

#include <map>
#include <string>

class PlayerContainer
{
public:
private:
	std::map<std::string, Player> m_leaguePlayers;
};