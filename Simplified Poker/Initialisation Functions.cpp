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
	const unsigned pot, const unsigned lastRaise, const unsigned maxBet)
{
	if (!players)
	{
		return;
	}

	std::cout << '\n' << "Pot: " << pot << '\n';
	std::cout << '\n' << "Player " << currentPlayer + 1 << "\n";
	std::cout << "You have given: " << players[currentPlayer].given << '\n';
	std::cout << "Amount to call to: " << maxBet << '\n';
	std::cout << "Minimum raise: " << lastRaise + CHIP_VALUE << "\n";

}

void showPlayerBalances(const Player* players, const unsigned short playerCount,
	const bool isTie)
{
	if (!players)
	{
		return;
	}

	if (isTie)
	{
		std::cout << "IT'S A TIE\n";
	}

	size_t toBePrinted = playerCount;
	const int PLAYERS_PER_ROW = 3;

	size_t current = 0;

	while (current < playerCount)
	{
		for (size_t row = 0; row < PLAYERS_PER_ROW && row < toBePrinted; row++)
		{
			/*if (!players[current].isActive)
			{
				current++;
				continue;
			}*/

			if (players[current].allIn)
			{
				std::cout << '*';
			}
			std::cout << "Player " << current + 1 << ": " << players[current].chips << " ";
			current++;
		}

		toBePrinted -= PLAYERS_PER_ROW;

		std::cout << '\n';
	}
}

void printInfoHeader(const Player* players, const unsigned short playerCount, const size_t currentPlayer,
	const unsigned pot, const unsigned lastRaise, const unsigned maxBet,
	const bool isTie, char& playerAnswer)
{
	showPlayerBalances(players, playerCount, isTie);
	printPlayerInfo(players, currentPlayer, pot, lastRaise, maxBet);
	askPlayerToPrintDeck(players[currentPlayer], playerAnswer);
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

void printWinnersHeader(const Player* players, const unsigned short playerCount, 
	const unsigned pot, size_t& winnerCount)
{
	std::cout << "Pot: " << pot << '\n';
	std::cout << ((winnerCount > 1) ? ("\nIT'S A TIE!\n") : ("\nWinner is : "));
	printWinners(players, playerCount);
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

void finalisePlayerDecks(Player* players, const unsigned short playerCount, 
	unsigned& pot)
{
	for (size_t playerIndx = 0; playerIndx < playerCount; playerIndx++)
	{
		if (players[playerIndx].isActive)
		{
			orderPlayerCards(players[playerIndx]);
			players[playerIndx].points = calculatePlayerPoints(players[playerIndx].cards);


			if (players[playerIndx].chips <= CHIP_VALUE)
			{
				players[playerIndx].chips = 0;
				players[playerIndx].allIn = true;
			}
			else
			{
				players[playerIndx].chips -= CHIP_VALUE;
			}

			pot += CHIP_VALUE;
		}
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

		players[indx].allIn = false;
	}
}

void resetGameParams(Player*& players, size_t& currentPlayer,
	const unsigned short playerCount, unsigned& lastRaise,
	unsigned& pot, unsigned short& inGame, size_t& lastPlayerToRaise, 
	unsigned& maxBet, bool& isTie)
{
	inGame = 0;
	pot = 0;
	lastRaise = 0;
	currentPlayer = 0;
	lastPlayerToRaise = 0;
	maxBet = 0;
	isTie = false;
	resetPlayerStates(players, playerCount, inGame);
}

void readyPlayersForTie(Player*& players, const unsigned short playerCount,
	unsigned short& inGame, const unsigned pot, char& playerAnswer,
	unsigned& lastRaise, unsigned& maxBet, bool& isTie)
{
	if (!players)
	{
		return;
	}

	lastRaise = 0;
	maxBet = 0;
	isTie = true;

	for (size_t indx = 0; indx < playerCount; indx++)
	{
		if (players[indx].isActive)
		{
			if (players[indx].allIn)
			{
				players[indx].chips += TIE_COMPENSATION;
				players[indx].allIn = false;
			}

			players[indx].given = 0;
			players[indx].allIn = false;
		}
		else
		{
			if(players[indx].chips > 0)
				askPlayerToJoinTie(players[indx], indx, pot, inGame, playerAnswer);
		}
	}
}

unsigned countActiveOrNotAllInPlayers(const Player* players, const unsigned short playerCount)
{
	if (!players)
	{
		return 0;
	}

	unsigned count = 0;
	for (size_t indx = 0; indx < playerCount; indx++)
	{
		if (players[indx].isActive && !players[indx].allIn)
		{
			count++;
		}
	}

	return count;
}

void playerAction(Player* players, const size_t currentPlayer,
	const unsigned short playerCount, char& playerAnswer, unsigned& lastRaise,
	unsigned& pot, unsigned short& inGame,
	size_t& lastPlayerToRaise, unsigned& maxBet, unsigned& minBalance)
{
	if (!players)
	{
		return;
	}

	askPlayerAction(players[currentPlayer], maxBet, currentPlayer, playerAnswer, 
		players, playerCount, lastRaise, minBalance);
	playPlayerAction(players, currentPlayer, playerCount, playerAnswer, lastRaise, 
		pot, inGame, lastPlayerToRaise, maxBet, minBalance);
}