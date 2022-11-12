#pragma once

#include <string>

class Player
{
public:
	Player() = delete;
	Player(std::string firstName, std::string lastName, int yearOfBirth, std::string category, bool registered);

	std::string getLast() { return lastName; }

private:
	std::string m_firstName;
	std::string m_lastName;
	int m_yearOfBirth;
	std::string m_category;
	bool m_paidStatus;
};