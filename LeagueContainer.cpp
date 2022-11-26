#include "leaguecontainer.h"
#include "player.h"

#include <list>
#include <iostream>
#include <fstream>

void LeagueContainer::startNewSeason()
{
	int year;

	std::cout << "\033c" // Clears the screen
			  << "Start a New Season" << std::endl
			  << "--------------------" << std::endl;

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
			m_leaguePlayers.clear();
			break;
		}
	}
	m_currentYear = year;
}

void LeagueContainer::addPlayer()
{
	std::string firstName;
	std::string lastName;
	int32_t yearOfBirth;
	char paidIntermediate[4];
	bool paid;

	std::cout << "\033c" // Clears the screen
			  << "Add Player" << std::endl
			  << "------------" << std::endl;

	std::cout << "First Name: ";
	std::getline(std::cin, firstName);

	std::cout << "Last Name: ";
	std::getline(std::cin, lastName);

	std::cout << "Birth Year: ";
	std::cin >> yearOfBirth;

	std::cout << "Have they paid the registration fee? (y/n)" << std::endl
			  << ">>> ";
	std::cin >> paidIntermediate;
	if (toupper(paidIntermediate[0]) == 'Y')
	{
		paid = true;
	}
	else
	{
		paid = false;
	}

	m_leaguePlayers.emplace(std::make_pair(lastName + firstName, Player(m_currentYear, firstName, lastName, yearOfBirth, paid)));
}

void LeagueContainer::printStatistics()
{
	int under6Count = 0, under8Count = 0, under10Count = 0, under12Count = 0, under14Count = 0, under17Count = 0;
	int paidCount = 0;

	for (auto player : m_leaguePlayers)
	{
		if (player.second.getCategory() == "U6")
		{
			under6Count++;
		}
		else if (player.second.getCategory() == "U8")
		{
			under8Count++;
		}
		else if (player.second.getCategory() == "U10")
		{
			under10Count++;
		}
		else if (player.second.getCategory() == "U12")
		{
			under12Count++;
		}
		else if (player.second.getCategory() == "U14")
		{
			under14Count++;
		}
		else if (player.second.getCategory() == "U17")
		{
			under17Count++;
		}

		if (player.second.paymentStatus())
		{
			paidCount++;
		}
	}

	std::cout << "\033c" // Clears the screen
			  << "Statistics" << std::endl
			  << "------------" << std::endl
			  << "Total number of players: " << m_leaguePlayers.size() << std::endl
			  << std::endl
			  << "Paid: " << paidCount << std::endl
			  << "Not paid: " << m_leaguePlayers.size() - paidCount << std::endl
			  << std::endl
			  << "Players in U6: " << under6Count << std::endl
			  << "Players in U8: " << under8Count << std::endl
			  << "Players in U10: " << under10Count << std::endl
			  << "Players in U12: " << under12Count << std::endl
			  << "Players in U14: " << under14Count << std::endl
			  << "Players in U17: " << under17Count << std::endl
			  << "-----------------------------" << std::endl
			  << "Press enter to return to menu" << std::endl;
	std::cin.get();
}

void LeagueContainer::saveSearchToFile(std::list<Player> &searchResult)
{
	std::ofstream outfile("search_result.txt");
	for (auto &player : searchResult)
	{
		outfile << player << std::endl;
	}
}

std::list<Player> LeagueContainer::searchForPlayers(bool &foundMatches) const
{
	std::string tempFirstName = "", tempLastName = "", tempBirthYear = "", tempCategory = "", tempKeyword = "", tempPaidString = "";
	bool tempPaidBool = false;
	std::list<Player> searchResult;

	std::cout << "\033c" // Clears the screen
			  << "If you wish to search by a specific condition, enter a value, else press enter to go to the next condition" << std::endl
			  << "---------------------------------------------------------------" << std::endl
			  << "First name: ";
	if (std::cin.peek() != '\n')
	{
		std::getline(std::cin, tempFirstName);
	}
	else
	{
		std::cin.get(); // Catches the newline character from the above peek to prevent next condition from being skipped
	}
	std::cout << "Last name: ";
	if (std::cin.peek() != '\n')
	{
		std::getline(std::cin, tempLastName);
	}
	else
	{
		std::cin.get(); // Catches the newline character from the above peek to prevent next condition from being skipped
	}
	std::cout << "Category: ";
	if (std::cin.peek() != '\n')
	{
		std::getline(std::cin, tempCategory);
		tempCategory[0] = toupper(tempCategory[0]);
		std::cout << tempCategory << std::endl;
	}
	else
	{
		std::cin.get(); // Catches the newline character from the above peek to prevent next condition from being skipped
	}
	std::cout << "Keyword (First Name or Last Name): ";
	if (std::cin.peek() != '\n')
	{
		std::getline(std::cin, tempKeyword);
	}
	else
	{
		std::cin.get(); // Catches the newline character from the above peek to prevent next condition from being skipped
	}
	std::cout << "Paid (y/n): ";
	if (std::cin.peek() != '\n')
	{
		std::getline(std::cin, tempPaidString);
		if (toupper(tempPaidString[0]) == 'Y')
		{
			tempPaidBool = true;
		}
	}

	// Search Conditions
	bool firstNameMatches = true;
	bool lastNameMatches = true;
	bool categoryMatches = true;
	bool keywordMatches = true;
	bool paidStatusMatches = true;

	for (auto player : m_leaguePlayers)
	{
		if (tempFirstName != "")
		{
			firstNameMatches = (tempFirstName == player.second.getFirst());
		}
		if (tempLastName != "")
		{

			lastNameMatches = (tempLastName == player.second.getLast());
		}
		if (tempCategory != "")
		{
			categoryMatches = (tempCategory == player.second.getCategory());
		}
		if (tempKeyword != "")
		{
			keywordMatches = (tempKeyword == player.second.getFirst() || tempKeyword == player.second.getLast());
		}

		paidStatusMatches = (tempPaidBool == player.second.paymentStatus());

		if (firstNameMatches && lastNameMatches && categoryMatches && keywordMatches && paidStatusMatches)
		{
			searchResult.push_back(player.second);
		}
	}
	if (searchResult.empty())
		foundMatches = false;

	return searchResult;
}

void LeagueContainer::saveLeagueToFile()
{
	std::ofstream outfile("league_data.txt");
	for (auto player : m_leaguePlayers)
	{
		if (player.second.getCategory() == "U")
		{
		}
	}
}