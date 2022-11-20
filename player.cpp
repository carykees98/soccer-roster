#include "player.h"

#include <string>
#include <iostream>

Player::Player(int32_t currentYear, std::string firstName, std::string lastName, int32_t yearOfBirth, bool paidStatus = false)
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
		out << "Paid" << std::endl;
	}
	else
	{
		out << "Not Paid" << std::endl;
	}
	return out;
}