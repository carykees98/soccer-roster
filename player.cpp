#include "Player.h"

#include <string>

Player::Player(int yearOfBirth, std::string category, bool paid = false)
{
	m_yearOfBirth = yearOfBirth;
	m_category = category;
	m_paid = paid;
}