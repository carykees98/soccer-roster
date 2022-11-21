#pragma once

#include <string>
#include <iostream>

class Player
{
public:
	Player() = delete;
	Player(int32_t currentYear, std::string firstName, std::string lastName, int32_t yearOfBirth, bool paidStatus);

	std::string getLast() { return m_lastName; }
	std::string getFirst() { return m_firstName; }
	std::string getCategory() { return m_category; }
	bool paymentStatus() { return m_paidStatus; }

	void editPlayer();

	friend std::ostream &operator<<(std::ostream &out, Player &toPrint);

private:
	std::string determineCategory(int32_t currentYear);

private:
	std::string m_firstName;
	std::string m_lastName;
	int32_t m_yearOfBirth;
	std::string m_category;
	bool m_paidStatus;
};