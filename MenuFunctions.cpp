#include "MenuFunctions.h"
#include "LeagueContainer.h"

#include <iostream>
#include <iomanip>

void mainMenu(LeagueContainer &league)
{
	std::cout << "\033c";
	std::cout << "Main Menu" << std::endl
			  << "-------------" << std::endl;
}

void searchMenu(LeagueContainer &league)
{
	int menuChoice;
	while (true)
	{

		std::cout << "Search Menu" << std::endl
				  << "-------------" << std::endl
				  << "1. " << std::left << "Search" << std::endl
				  << "2. " << std::left << "Next result" << std::endl
				  << "3. " << std::left << "Previous result" << std::endl
				  << "4. " << std::left << "Edit player" << std::endl
				  << "5. " << std::left << "Save search result to file" << std::endl
				  << "6. " << std::left << "Exit search results mode" << std::endl
				  << "7. " << std::left << "Exit Program" << std::endl;

		std::cin >> menuChoice;
		switch (menuChoice)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			std::exit(0);
			break;
		default:
			std::cerr << "Please enter a valid choice (1-7)";
		}
	}
}

void runSearch(LeagueContainer &league)
{
	std::cout << "Search by: " << std::endl;
}