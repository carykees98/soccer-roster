#pragma once

#include <string>

class Player
{
public:
	Player() = delete;
	Player(int yearOfBirth, std::string category, bool registered);

private:
	int m_yearOfBirth;
	std::string m_category;
	bool m_paid;
};