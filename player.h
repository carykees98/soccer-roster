#pragma once

#include <string>

class Player
{
public:
	Player() = delete;
	Player(int32_t currentYear, std::string firstName, std::string lastName, int32_t yearOfBirth, bool paidStatus = false);

	std::string getLast() { return m_lastName; }
	std::string getFirst() { return m_firstName; }

private:
	std::string determineCategory(int32_t currentYear);

private:
	std::string m_firstName;
	std::string m_lastName;
	int32_t m_yearOfBirth;
	std::string m_category;
	bool m_paidStatus;
};