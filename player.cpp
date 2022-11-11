#include "Player.h"

#include <string>

Player::Player(std::string firstName, std::string lastName, int yearOfBirth, std::string category, bool paidStatus = false)
{
	m_firstName = firstName;
	m_lastName = lastName;
	m_yearOfBirth = yearOfBirth;
	m_category = category;
	m_paidStatus = paidStatus;
}