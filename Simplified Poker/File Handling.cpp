#include <fstream>
#include <iostream>
#include "File Handling.h"

const char* FILE_NAME = "game info.txt";

char BUFFER[1024]{};

void enterGameInfo(const Player* players, const unsigned short playerCount)
{
	if (!players)
	{
		return;
	}

	std::ofstream ofs(FILE_NAME);
	if (!ofs.is_open())
	{
		return;
	}

	ofs << playerCount << '\n';
	for (size_t indx = 0; indx < playerCount; indx++)
	{
		ofs << players[indx].chips << '\n';
	}

	ofs.close();
}

bool getGameInfo(Player* players, unsigned short& playerCount)
{

	std::ifstream ifs(FILE_NAME);
	if (!ifs.is_open())
	{
		std::cout << "Cound not open file";
		return false;
	}

	ifs >> playerCount;
	players = new Player[playerCount];

	for (size_t indx = 0; indx < playerCount; indx++)
	{
		ifs >> players[indx].chips;
	}

	ifs.close();

	return true;
}