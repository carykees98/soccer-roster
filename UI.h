#pragma once

#include "LeagueContainer.h"

class UI
{
public:
	void run();

private:
	void toggleModes();
	void menu();

private:
	LeagueContainer m_Players;
};