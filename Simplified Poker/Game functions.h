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
* <header file for helper functions that are used to execute game mechanics>
*
*/

#include "Player Structures.h"
#include "Deck Structures.h"
#include "Initialisation Functions.h"

void orderTwoCardsInPlayerHand(Card& firstCard, Card& secondCard);

void orderPlayerCards(Player& player);

bool isSevenOfClubs(const Card card);

short sumCardValues(const Card* playerCards, size_t startIndex);

short countIdenticalCardTypes(const Card* playerCards, size_t startIndex);

short countIdenticalCardSuits(const Card* playerCards, size_t startIndex);

unsigned short calculatePlayerPoints(const Card* playerCards);

unsigned calculateMinPlayerBalance(const Player* players, const unsigned short playerCount);

void raise(Player& player, const Player* allPlayers,
	const unsigned short playerCount, 
	unsigned& lastRaise, unsigned& pot, unsigned& maxBet, const unsigned minBalance);

void call(Player& player, unsigned& maxBet, unsigned& pot);

void fold(Player& player);

void playPlayerAction(Player* players, const size_t currentPlayer,
	const unsigned short playerCount, const char playerAnswer, unsigned& lastRaise,
	unsigned& pot, unsigned short& inGame, 
	size_t& lastPlayerToRaise, unsigned& maxBet, const unsigned minBalance);

unsigned getMaxPoints(const Player* players, const unsigned short playerCount);

void getWinners(Player* players, const unsigned short playerCount, const unsigned maxPoints,
	unsigned& winnerCount, size_t& winnerIndx);

void bettingPhase(Player* players, size_t& currentPlayer,
	const unsigned short playerCount, char& playerAnswer, unsigned& lastRaise,
	unsigned& pot, unsigned short& inGame, size_t& lastPlayerToRaise, unsigned& maxBet,
	unsigned& minBalance, bool& isTie);

