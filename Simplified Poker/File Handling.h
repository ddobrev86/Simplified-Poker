#pragma once
#include "Player Structures.h"

void saveGameInfo(const Player* players, const unsigned short playerCount);

bool getGameInfo(Player*& players, unsigned short& playerCount, unsigned short& inGame);