#include <fstream>
#include <iostream>
#include "File Handling.h"

const char* FILE_NAME = "game info.txt";

char BUFFER[1024]{};

void saveGameInfo(const Player* players, const unsigned short playerCount)
{
	if (!players)
	{
		std::cout << "Could not save current game\n";
		return;
	}

	std::ofstream ofs(FILE_NAME);
	if (!ofs.is_open())
	{
		std::cout << "Could not save current game\n";
		return;
	}

	ofs << playerCount << '\n';
	for (size_t indx = 0; indx < playerCount; indx++)
	{
		ofs << players[indx].chips << '\n';
	}

	ofs.close();
	std::cout << "Game saved successfully\n";
}

bool getGameInfo(Player*& players, unsigned short& playerCount, unsigned short& inGame)
{

	std::ifstream ifs(FILE_NAME);
	if (!ifs.is_open())
	{
		return false;
	}

	ifs >> playerCount;
	players = new Player[playerCount];

	for (size_t indx = 0; indx < playerCount; indx++)
	{
		ifs >> players[indx].chips;

		if (players[indx].chips > 0)
			inGame++;
		else
			players[indx].isActive = false;
	}

	ifs.close();

	return true;
}