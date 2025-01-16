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
* <file with definitions for helper functions that initialise the game or print information>
*
*/

#include "Initialisation Functions.h"
#include <iostream>
//#include <cstdlib>
#include <stdlib.h>
#include <ctime>
//#include <algorithm>

const unsigned TIE_COMPENSATION = 5 * CHIP_VALUE;

void printGameCommands()
{
	std::cout << "1. Start new game" << std::endl
		<< "2. Continue saved game" << std::endl
		<< "3. Close program" << std::endl
		<< "Choose an option: ";
}

void printDeck(const Card* deck, const unsigned cardsCount, const char separator)
{
	for (size_t i = 0; i < cardsCount; i++)
	{
		std::cout << deck[i].type->pip << deck[i].suit->name << separator;
	}
}

void printPlayers(const Player* players, const unsigned short playerCount)
{
	for (size_t i = 0; i < playerCount; i++)
	{
		printDeck(players[i].cards, 3, '\n');
		std::cout << '\n' << calculatePlayerPoints(players[i].cards) << '\n' << '\n';
	}
}

void printPlayerInfo(const Player* players, const size_t currentPlayer,
	const unsigned pot, const unsigned lastRaise)
{
	if (!players)
	{
		return;
	}

	std::cout << '\n' << "Pot: " << pot << '\n';
	std::cout << '\n' << "Player " << currentPlayer + 1 << "\n";
	std::cout << "You have given: " << players[currentPlayer].given << '\n';
	std::cout << "Last raise is: " << lastRaise << '\n';
	std::cout << "Minimum raise: " << lastRaise + CHIP_VALUE << "\n\n";

}

void showPlayerBalances(const Player* players, const unsigned short playerCount)
{
	std::cout << '\n';

	size_t toBePrinted = playerCount;
	const int PLAYERS_PER_ROW = 3;

	for (size_t current = 0; current < playerCount;)
	{
		for (size_t row = 0; row < PLAYERS_PER_ROW && row < toBePrinted; row++)
		{
			std::cout << "Player " << ++current << ": " << players[current - 1].chips << " ";
		}

		toBePrinted -= PLAYERS_PER_ROW;

		std::cout << '\n';
	}
}

void printWinners(const Player* players, const unsigned short playerCount)
{
	if (!players)
	{
		return;
	}

	for (size_t indx = 0; indx < playerCount; indx++)
	{
		if (players[indx].isActive)
		{
			std::cout << "Player " << indx + 1 << "\t";
		}
	}

	std::cout << std::endl;
}

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

void swapCards(Card& firstCard, Card& secondCard)
{
	Card temp = firstCard;
	firstCard = secondCard;
	secondCard = temp;
}

void shuffleDeck(const unsigned cardsInDeck, Card* deck)
{
	if (!deck || cardsInDeck < 0)
	{
		std::cout << "Invalid input";
		return;
	}

	int rhs;
	srand(time(0));

	for (size_t lhs = 0; lhs < cardsInDeck; lhs++)
	{
		rhs = rand() % cardsInDeck;

		swapCards(*(deck + lhs), *(deck + rhs));
	}
}

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
			if (!players[currentPlayer].isActive)
				continue;

			players[currentPlayer].cards[currentCard] = *deck;
			deck++;
		}
	}
}

void finalisePlayerDecks(Player* players, const size_t playerCount, unsigned& pot)
{
	for (size_t playerIndx = 0; playerIndx < playerCount; playerIndx++)
	{
		orderPlayerCards(players[playerIndx]);
		players[playerIndx].points = calculatePlayerPoints(players[playerIndx].cards);

		players[playerIndx].chips -= CHIP_VALUE;
		//players[playerIndx].given += CHIP_VALUE;
		pot += CHIP_VALUE;
	}
}

void resetPlayerStates(Player*& players, const unsigned short playerCount,
	unsigned short& inGame)
{
	if (!players)
	{
		return;
	}

	for (size_t indx = 0; indx < playerCount; indx++)
	{
		if (players[indx].chips > 0)
		{
			players[indx].isActive = true;
			players[indx].given = 0;
			inGame++;
		}
	}
}

void readyPlayersForTie(Player*& players, const unsigned short playerCount,
	unsigned short& inGame, const unsigned pot)
{
	if (!players)
	{
		return;
	}

	for (size_t indx = 0; indx < playerCount; indx++)
	{
		if (players[indx].isActive)
		{
			if (players[indx].chips == 0)
			{
				players[indx].chips += TIE_COMPENSATION;
			}
		}
		else
		{
			askPlayerToJoinTie(players[indx], indx, pot, inGame);
		}
	}
}