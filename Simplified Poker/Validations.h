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
* <header file for functions that validate user input>
*
*/

#include "Player Structures.h"
#include "Initialisation Functions.h"

void enterPlayerCount(unsigned short& playerCount);

void askPlayerAction(const Player player, const unsigned maxBet,
	const size_t playerIndx, char& playerAnswer);

void askPlayerToPrintDeck(Player player, char& playerAnswer);

void playAgain(char& answer);

void askPlayerToJoinTie(Player player, const size_t indx, 
	const unsigned pot, unsigned short& inGame);