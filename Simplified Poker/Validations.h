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
#include "Game functions.h"

void askPlayerYesOrNo(char& playerAnswer);

void enterPlayerCount(unsigned short& playerCount);

void askPlayerAction(const Player player, const unsigned maxBet,
	const size_t playerIndx, char& playerAnswer, const Player* players,
	const unsigned short playerCount, const unsigned lastRaise,
	unsigned& minBalance);

void askPlayerToPrintDeck(const Player player, char& playerAnswer);

void askToGoAllIn(char& playerAnswer);

void playAgain(char& playerAnswer);

void askPlayerToJoinTie(Player& player, const size_t indx, 
	const unsigned pot, unsigned short& inGame, char& playerAnswer);

void askToSaveGame(char& playerAnswer);