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
const unsigned CHIP_VALUE = 10;
const unsigned STARTING_CHIP_COUNT = 100;

struct Player
{
	bool isActive;
	bool allIn = false;
	unsigned short points;
	unsigned chips = STARTING_CHIP_COUNT * CHIP_VALUE;
	unsigned given = 0;
	Card cards[CARDS_PER_PLAYER]{};
};
