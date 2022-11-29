#include "MenuFunctions.h"
#include "LeagueContainer.h"

int main(int argc, char const *argv[])
{
	LeagueContainer league;
	league.readFromLastSession();
	mainMenu(league);
	return 0;
}
