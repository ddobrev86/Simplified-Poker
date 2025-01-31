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
* <header file for functions that are used to execute game mechanics>
*
*/

#include "Player Structures.h"
#include "Deck Structures.h"
#include "Initialisation Functions.h"
#include "File Handling.h"

void orderTwoCardsInPlayerHand(Card& firstCard, Card& secondCard);

void orderPlayerCards(Player& player);

bool isSevenOfClubs(const Card card);

short sumCardValues(const Card* playerCards, size_t startIndex, bool& gameState);

short countIdenticalCardTypes(const Card* playerCards, size_t startIndex, bool& gameState);

short countIdenticalCardSuits(const Card* playerCards, size_t startIndex, bool& gameState);

unsigned short calculatePlayerPoints(const Card* playerCards, bool& gameState);

unsigned calculateMinPlayerBalance(const Player* players, const unsigned short playerCount, bool& gameState);

void raise(Player& player, const Player* allPlayers, const unsigned short playerCount, 
	unsigned& lastRaise, unsigned& pot, unsigned& maxBet, const unsigned minBalance, bool& gameState);

void call(Player& player, unsigned& maxBet, unsigned& pot);

void fold(Player& player);

void playPlayerAction(Player* players, const size_t currentPlayer, const unsigned short playerCount, 
	const char playerAnswer, unsigned& lastRaise, unsigned& pot, unsigned short& inGame,
	size_t& lastPlayerToRaise, unsigned& maxBet, const unsigned minBalance, bool& gameState);

void playerAction(Player* players, const size_t currentPlayer, const unsigned short playerCount, 
	char& playerAnswer, unsigned& lastRaise, unsigned& pot, unsigned short& inGame,
	size_t& lastPlayerToRaise, unsigned& maxBet, unsigned& minBalance, bool& gameState);

unsigned getMaxPoints(const Player* players, const unsigned short playerCount, bool& gameState);

void getWinners(Player* players, const unsigned short playerCount, const unsigned maxPoints,
	unsigned& winnerCount, size_t& winnerIndx, bool& gameState);

void bettingPhase(Player* players, size_t& currentPlayer, const unsigned short playerCount, 
	char& playerAnswer, unsigned& lastRaise, unsigned& pot, unsigned short& inGame, 
	size_t& lastPlayerToRaise, unsigned& maxBet, unsigned& minBalance, bool& isTie, bool& gameState);

void endOfGame(Player*& players, const unsigned short playerCount, unsigned short& inGame,
	const unsigned pot, char& playerAnswer, unsigned& lastRaise, unsigned& maxBet, bool& isTie, 
	const unsigned winnerCount, const size_t winnerIndx, size_t& currentPlayer, 
	size_t& lastPlayerToRaise, bool& gameState);

void playGame(Player* players, unsigned short& playerCount,
	Card* deck, const unsigned CARDS_IN_DECK, unsigned short inGame);

