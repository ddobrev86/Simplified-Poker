#pragma once
/**
*
* Solution to course project # 10
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Dimitar Dobrev
* @idnumber 3MI0600520
* @compiler VC
*
* <header file for functions that work with files>
*
*/

#include "Player Structures.h"

void saveGameInfo(const Player* players, const unsigned short playerCount);

bool getGameInfo(Player*& players, unsigned short& playerCount, unsigned short& inGame);