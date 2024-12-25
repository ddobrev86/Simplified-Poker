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
* <file with definitions for helper functions that initialise the game>
*
*/

#include "Initialisation Functions.h"
#include <iostream>

Card* fillDeckWithCards(const CardType* cardTypes, const CardSuit* cardSuites, 
	const unsigned typesCount, const unsigned suitsCount, const unsigned cardsCount)
{
	if (!cardTypes || !cardSuites)
	{
		std::cout << "Invalid input";
		return nullptr;
	}

	Card* deck = new Card[suitsCount * typesCount];

	for (size_t currentCardType = 0; currentCardType < typesCount; currentCardType++)
	{
		for (size_t currentSuit = 0; currentSuit < suitsCount; currentSuit++)
		{
			deck->type = &cardTypes[currentCardType];
			deck->suit = &cardSuites[currentSuit];
			deck++;
		}
	}

	deck -= cardsCount;

	return deck;
}

//void shuffleDeck(const unsigned cardsInDeck, Card* deck)
//{
//	if (!deck || cardsInDeck < 0)
//	{
//		std::cout << "Invalid input";
//		return;
//	}
//
//	for (size_t lhs = 0; lhs < cardsInDeck; lhs++)
//	{
//
//	}
//}

void dealCardsToPlayers(const unsigned short playerCount, const unsigned short cardsPerPlayer,
	Card* deck, Player* players)
{
	if (!deck || !players)
	{
		std::cout << "Invalid input";
		return;
	}

	for (size_t currentCard = 0; currentCard < cardsPerPlayer; currentCard++)
	{
		for (size_t currentPlayer = 0; currentPlayer < playerCount; currentPlayer++)
		{
			players[currentPlayer].cards[currentCard] = *deck;
			deck++;
		}
	}
}