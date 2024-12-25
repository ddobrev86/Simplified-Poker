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
* <header file for all structures, connected to the player>
*
*/

#pragma once
#include "Deck Structures.h"

const unsigned short CARDS_PER_PLAYER = 3;

struct Player
{
	bool isActive;
	bool outOfChips = false;
	//unsigned short orderInGame;
	unsigned int chips;
	Card cards[CARDS_PER_PLAYER];
};
