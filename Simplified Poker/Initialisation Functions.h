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
* <header file for helper functions that initialise the game>
*
*/

#pragma once
#include "Deck Structures.h"
#include "Player Structures.h"
#include "Game functions.h"

void printGameCommands();

void printDeck(const Card* deck, const unsigned cardsCount, const char separator);

void printPlayers(const Player* players, const unsigned short playerCount);

void showPlayerBalances(const Player* players, const unsigned short playerCount);

void printWinners(const Player* players, const unsigned short playerCount);

Card* fillDeckWithCards(const CardType* cardTypes, const CardSuit* cardSuites,
	const unsigned typesCount, const unsigned suitsCount, const unsigned cardsCount);

void swapCards(Card& firstCard, Card& secondCard);

void shuffleDeck(const unsigned cardsInDeck, Card* deck);

void dealCardsToPlayers(const unsigned short playerCount, const unsigned short cardsPerPlayer, 
	Card* deck, Player* players);
