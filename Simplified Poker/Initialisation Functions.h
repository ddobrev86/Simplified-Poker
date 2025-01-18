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
* <header file for helper functions that initialise the game or print information>
*
*/

#pragma once
#include "Deck Structures.h"
#include "Player Structures.h"
#include "Game functions.h"
#include "Validations.h"

void printGameCommands();

void printDeck(const Card* deck, const unsigned cardsCount, const char separator);

void printPlayers(const Player* players, const unsigned short playerCount);

void printPlayerInfo(const Player* players, const size_t currentPlayer,
	const unsigned pot, const unsigned lastRaise, const unsigned maxBet);

void showPlayerBalances(const Player* players, const unsigned short playerCount);

void printWinners(const Player* players, const unsigned short playerCount);

Card* fillDeckWithCards(const CardType* cardTypes, const CardSuit* cardSuites,
	const unsigned typesCount, const unsigned suitsCount, const unsigned cardsCount);

void swapCards(Card& firstCard, Card& secondCard);

void shuffleDeck(const unsigned cardsInDeck, Card* deck);

void dealCardsToPlayers(const unsigned short playerCount, const unsigned short cardsPerPlayer, 
	Card* deck, Player* players);

void finalisePlayerDecks(Player* players, const size_t playerCount, unsigned& pot);

void resetPlayerStates(Player*& players, const unsigned short playerCount,
	unsigned short& inGame);

void resetGameParams(Player*& players, size_t& currentPlayer,
	const size_t playerCount, unsigned& lastRaise,
	unsigned& pot, unsigned short& inGame, size_t& lastPlayerToRaise, unsigned& maxBet);

void readyPlayersForTie(Player*& players, const unsigned short playerCount,
	unsigned short& inGame, const unsigned pot);
