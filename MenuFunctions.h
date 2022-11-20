#pragma once

#include "leaguecontainer.h"
#include "player.h"

void mainMenu(LeagueContainer &league);

void searchMenu(LeagueContainer &league);

std::list<Player> runSearch(LeagueContainer &league);