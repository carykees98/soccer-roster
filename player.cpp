#include "player.h"

#include <string>
#include <iostream>

Player::Player(int currentYear, std::string firstName, std::string lastName, int yearOfBirth, bool paidStatus = false)
{
	m_firstName = firstName;
	m_lastName = lastName;
	m_yearOfBirth = yearOfBirth;
	m_paidStatus = paidStatus;

	m_category = determineCategory(currentYear);
}

std::ostream &operator<<(std::ostream &out, Player &toPrint)
{
	out << toPrint.m_lastName << ", " << toPrint.m_firstName << " - " << toPrint.m_category << " ";
	if (toPrint.m_paidStatus)
	{
		out << "Paid";
	}
	else
	{
		out << "Not Paid";
	}
	return out;
}

std::string Player::determineCategory(int currentYear)
{
	int age = currentYear - m_yearOfBirth;
	if (age >= 4 && age < 6)
	{
		return "U4";
	}
	else if (age >= 6 && age < 8)
	{
		return "U8";
	}
	else if (age >= 8 && age < 10)
	{
		return "U10";
	}
	else if (age >= 10 && age < 12)
	{
		return "U12";
	}
	else if (age >= 12 && age < 14)
	{
		return "U14";
	}
	else if (age >= 14 && age < 17)
	{
		return "U17";
	}
	return "Invalid Age";
}

void Player::editPlayer()
{
	int menuChoice;
	std::string errorMessage = "";

	while (true)
	{
		std::cout << "\033c"; // Clears the screen
		if (errorMessage != "")
		{
			std::cerr << "Error: " + errorMessage << std::endl
					  << "-----------------------------------------" << std::endl;
		}
		std::cout << "Add Player" << std::endl
				  << "------------" << std::endl;
		std::cout << "Which field would you like to edit?" << std::endl
				  << "1. First name" << std::endl
				  << "2. Last name" << std::endl
				  << "3. Birth Year" << std::endl
				  << "4. Payment status" << std::endl
				  << "5. Exit" << std::endl;
		std::cin >> menuChoice;

		switch (menuChoice)
		{
		case 1:
			std::cout << "Please enter the new first name" << std::endl
					  << ">>> ";
			std::cin >> m_firstName;
			break;
		case 2:
			std::cin >> m_lastName;
			break;
		case 3:
			std::cin >> m_yearOfBirth;
			break;
		case 4:
			char statusAnswer[4];
			std::cout << "Has the player paid? (y/n)" << std::endl
					  << ">>> ";
			std::cin >> statusAnswer;
			if (toupper(statusAnswer[0]) == 'Y')
			{
				m_paidStatus = true;
			}
			else
			{
				m_paidStatus = false;
			}
		case 5:
			return;
		default:
			errorMessage = "Please choose a valid option (1-4)";
		}
	}
}