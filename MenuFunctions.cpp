#include "menufunctions.h"
#include "leaguecontainer.h"
#include "player.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <utility>

void mainMenu(LeagueContainer &league)
{
	int menuChoice;
	std::string errorMessage;
	while (true)
	{
		std::cout << "\033c"; // Clears the screen
		if (!errorMessage.empty())
		{
			std::cerr << "Error: " + errorMessage << std::endl;
			errorMessage.clear();
		}
		std::cout << "Main Menu" << std::endl
				  << "-----------" << std::endl
				  << "1. " << std::left << "Start new season" << std::endl
				  << "2. " << std::left << "Add a player" << std::endl
				  << "3. " << std::left << "Search" << std::endl
				  << "4. " << std::left << "Save league roster to file" << std::endl
				  << "5. " << std::left << "Statistics" << std::endl
				  << "6. " << std::left << "Exit program" << std::endl
				  << ">>> ";
		std::cin >> menuChoice;
		std::cin.get(); // Catches the newline character from above cin statement to prevent issues in below functions

		switch (menuChoice)
		{
		case 1:
			league.startNewSeason();
			break;
		case 2:
			league.addPlayer();
			break;
		case 3:
			searchMenu(league);
			break;
		case 4:
			league.saveLeagueToFile();
			break;
		case 5:
			league.printStatistics();
			break;
		case 6:
			std::exit(0);
			break;
		default:
			errorMessage = "Please choose a valid option (1-6)";
		}
	}
}

void searchMenu(LeagueContainer &league)
{
	int menuChoice;
	std::string errorMessage;
	std::list<std::pair<std::string, Player>> searchResult;
	bool foundMatches = true;
	int64_t currentResultNumber;

	searchResult = league.searchForPlayers(foundMatches);

	if (!foundMatches)
		return;

	auto currentResult = searchResult.begin();
	currentResultNumber = 1;

	while (true)
	{
		std::cout << "\033c"; // Clears the screen
		if (!errorMessage.empty())
		{
			std::cerr << "Error: " + errorMessage << std::endl;
			errorMessage.clear();
		}
		std::cout << "Search Menu" << std::endl
				  << "-------------" << std::endl;
		if (!searchResult.empty())
		{
			std::cout << "Result " << currentResultNumber << " of " << searchResult.size() << ":" << std::endl
					  << currentResult->second << std::endl
					  << "-------------------------------" << std::endl;
		}
		std::cout << "1. "
				  << "Search" << std::endl
				  << "2. "
				  << "Next result" << std::endl
				  << "3. "
				  << "Previous result" << std::endl
				  << "4. "
				  << "Edit player" << std::endl
				  << "5. "
				  << "Save search result to file" << std::endl
				  << "6. "
				  << "Exit search results mode" << std::endl
				  << "7. "
				  << "Exit program" << std::endl
				  << ">>> ";

		std::cin >> menuChoice;
		std::cin.get(); // Catches the newline character from above cin statement to prevent issues in below functions

		switch (menuChoice)
		{
		case 1:
			searchResult = league.searchForPlayers(foundMatches);
			currentResult = searchResult.begin();
			break;
		case 2:
			currentResult++;
			currentResultNumber++;
			if (currentResult == searchResult.end())
			{
				currentResult = searchResult.begin();
				currentResultNumber = 1;
			}
			break;
		case 3:
			if (currentResult == searchResult.begin())
			{
				currentResult = searchResult.end();
				currentResult--;
				currentResultNumber = searchResult.size();
			}
			else
			{
				currentResult--;
				currentResultNumber--;
			}
			break;
		case 4:
			currentResult->second.editPlayer(league.currentYear());
			break;
		case 5:
			league.saveSearchToFile(searchResult);
			break;
		case 6:
			league.update(searchResult);
			return; // returns to main menu
		case 7:
			std::exit(0);
			break;
		default:
			errorMessage = "Please enter a valid choice (1-7)";
		}
	}
}