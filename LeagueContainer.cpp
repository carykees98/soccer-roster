#include "LeagueContainer.h"

#include <list>
#include <iostream>

void LeagueContainer::startNewSeason()
{
	int year;
	std::cout << "Please enter a year for the season\n";

	while (true)
	{
		std::cout << ">>> ";
		std::cin >> year;
		if (std::cin.fail())
		{
			std::cerr << "Input is not a valid year. Please enter a year for the season\n";
			// Clears the input stream to prevent failbit from being set again
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		else
		{
			break;
		}
	}
	m_currentYear = year;
}