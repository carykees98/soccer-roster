#include "leaguecontainer.h"
#include "player.h"

#include <list>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <algorithm>

void LeagueContainer::startNewSeason()
{
	int newYear;

	std::cout << "\033c" // Clears the screen
			  << "Start a New Season" << std::endl
			  << "--------------------" << std::endl;

	std::cout << "Please enter a year for the season\n";

	while (true)
	{
		std::cout << ">>> ";
		std::cin >> newYear;
		if (std::cin.fail())
		{
			std::cerr << "Input is not a valid year. Please enter a year for the season\n";
			// Clears the input stream to prevent failbit from being set again
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		else
		{
			char response[4];
			std::cout << "Are you sure you want to continue, this action will remove all current players. (y/n)" << std::endl
					  << ">>> ";
			std::cin >> response;

			if (toupper(response[0]) != 'Y')
			{
				return;
			}

			m_leaguePlayers.clear();
			break;
		}
	}
	m_currentYear = newYear;
}

void LeagueContainer::addPlayer(std::string &errorMessage)
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
	if ((m_currentYear - yearOfBirth) < 4 || (m_currentYear - yearOfBirth) >= 17)
	{
		errorMessage = "Error: Player's age doesn't fall within the range of this league";
		return;
	}

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

	for (auto &player : m_leaguePlayers)
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

void LeagueContainer::saveSearchToFile(std::list<std::pair<std::string, Player>> &searchResult)
{
	std::string fileName;
	std::cout << "What would you like to name the file?" << std::endl
			  << ">>> ";
	std::cin >> fileName;
	std::ofstream outfile(fileName);
	for (auto &player : searchResult)
	{
		outfile << player.second << std::endl;
	}
}

std::list<std::pair<std::string, Player>> LeagueContainer::searchForPlayers(bool &foundMatches) const
{
	std::string tempFirstName = "", tempLastName = "", tempBirthYear = "", tempCategory = "", tempKeyword = "", tempPaidString = "";
	bool tempPaidBool = false;
	std::list<std::pair<std::string, Player>> searchResult;
	bool searchByPaid;

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
		searchByPaid = true;
	}
	else
	{
		searchByPaid = false;
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
		if (searchByPaid)
		{
			paidStatusMatches = (tempPaidBool == player.second.paymentStatus());
		}

		if (firstNameMatches && lastNameMatches && categoryMatches && keywordMatches && paidStatusMatches)
		{
			searchResult.push_back(player);
		}
	}

	if (searchResult.empty())
		foundMatches = false;

	return searchResult;
}

void LeagueContainer::saveLeagueToFile()
{
	std::string fileName;
	std::cout << "What would you like to name the file?" << std::endl
			  << ">>> ";
	std::cin >> fileName;
	std::ofstream outfile(fileName);

	std::vector<Player> under6Players;
	std::vector<Player> under8Players;
	std::vector<Player> under10Players;
	std::vector<Player> under12Players;
	std::vector<Player> under14Players;
	std::vector<Player> under17Players;

	for (auto &player : m_leaguePlayers)
	{
		if (player.second.getCategory() == "U6")
		{
			under6Players.push_back(player.second);
		}
		else if (player.second.getCategory() == "U8")
		{
			under8Players.push_back(player.second);
		}
		else if (player.second.getCategory() == "U10")
		{
			under10Players.push_back(player.second);
		}
		else if (player.second.getCategory() == "U12")
		{
			under12Players.push_back(player.second);
		}
		else if (player.second.getCategory() == "U14")
		{
			under14Players.push_back(player.second);
		}
		else if (player.second.getCategory() == "U17")
		{
			under17Players.push_back(player.second);
		}
	}
	if (!under6Players.empty())
	{
		std::sort(under6Players.begin(), under6Players.end());
		outfile << "U6" << std::endl;
		for (Player player : under6Players)
		{
			outfile << player << std::endl;
		}
		outfile << std::endl;
	}
	if (!under8Players.empty())
	{
		std::sort(under8Players.begin(), under8Players.end());
		outfile << "U8" << std::endl;
		for (Player player : under8Players)
		{
			outfile << player << std::endl;
		}
		outfile << std::endl;
	}
	if (!under10Players.empty())
	{
		std::sort(under10Players.begin(), under10Players.end());
		outfile << "U10" << std::endl;
		for (Player player : under10Players)
		{
			outfile << player << std::endl;
		}
		outfile << std::endl;
	}
	if (!under12Players.empty())
	{
		std::sort(under12Players.begin(), under12Players.end());
		outfile << "U12" << std::endl;
		for (Player player : under12Players)
		{
			outfile << player << std::endl;
		}
		outfile << std::endl;
	}
	if (!under14Players.empty())
	{
		std::sort(under14Players.begin(), under14Players.end());
		outfile << "U14" << std::endl;
		for (Player player : under14Players)
		{
			outfile << player << std::endl;
		}
		outfile << std::endl;
	}
	if (!under17Players.empty())
	{
		std::sort(under17Players.begin(), under17Players.end());
		outfile << "U17" << std::endl;
		for (Player player : under17Players)
		{
			outfile << player << std::endl;
		}
		outfile << std::endl;
	}
}

void LeagueContainer::update(std::list<std::pair<std::string, Player>> &searchResult)
{
	for (auto &player : searchResult)
	{
		if (m_leaguePlayers.find(player.first)->second != player.second)
		{
			m_leaguePlayers.erase(player.first);
			m_leaguePlayers.insert(std::pair<std::string, Player>(player.second.getLast() + player.second.getFirst(), player.second));
		}
	}
}

void LeagueContainer::saveForNextSession()
{
	std::ofstream outfile("league.dat");

	outfile << m_currentYear << " " << m_leaguePlayers.size() << std::endl;

	for (auto &player : m_leaguePlayers)
	{
		outfile << player.second.getFirst() << std::endl
				<< player.second.getLast() << std::endl
				<< player.second.birthYear() << " " << player.second.paymentStatus() << std::endl;
	}
}

void LeagueContainer::readFromLastSession()
{
	int numberOfRecords;
	std::ifstream infile("league.dat");

	infile >> m_currentYear >> numberOfRecords;
	infile.get(); // catches newline character

	std::string tempFirst;
	std::string tempLast;
	int tempBirthYear;
	bool tempPaymentStatus;

	for (size_t i = 0; i < numberOfRecords; i++)
	{
		std::getline(infile, tempFirst);
		std::getline(infile, tempLast);
		infile >> tempBirthYear >> tempPaymentStatus;
		infile.get();

		m_leaguePlayers.insert(std::pair<std::string, Player>(tempLast + tempFirst, Player(m_currentYear, tempFirst, tempLast, tempBirthYear, tempPaymentStatus)));
	}
}