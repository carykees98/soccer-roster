#include "Player.h"

#include <string>

Player::Player(int32_t currentYear, std::string firstName, std::string lastName, int32_t yearOfBirth, bool paidStatus = false)
{
	m_firstName = firstName;
	m_lastName = lastName;
	m_yearOfBirth = yearOfBirth;
	m_paidStatus = paidStatus;

	m_category = determineCategory(currentYear);
}
