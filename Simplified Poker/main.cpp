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
* <main file>
* 
*/

#include <iostream>
#include "Deck Structures.h"
#include "Initialisation Functions.h"
#include "Player Structures.h"

const unsigned TYPES_COUNT = 8;
const unsigned SUITS_COUNT = 4;
const unsigned CARDS_IN_DECK = TYPES_COUNT * SUITS_COUNT;

const CardType CARD_TYPES[] = {
	{"7", 7},
	{"8", 8},
	{"9", 9},
	{"10", 10},
	{"J", 10},
	{"D", 10},
	{"K", 10},
	{"A", 11}
};

const CardSuit SUITS[] = {
	{'C', 1},
	{'D', 2},
	{'H', 3},
	{'S', 4},
};

Card* deck = fillDeckWithCards(CARD_TYPES, SUITS, TYPES_COUNT, SUITS_COUNT, CARDS_IN_DECK);

void printDeck(const Card* deck, const unsigned cardsCount)
{
	for (size_t i = 0; i < cardsCount; i++)
	{
		std::cout << deck[i].type->pip << deck[i].suit->name << std::endl;
	}
}

void printPlayers(const Player* players, const unsigned playerCount)
{
	for (size_t i = 0; i < playerCount; i++)
	{
		printDeck(players[i].cards, 3);
		std::cout << '\n';
	}
}

int main()
{
	char gameCommand;
	unsigned short playerCount;

	while (true)
	{
		printGameCommands();
		std::cin >> gameCommand;
		switch (gameCommand)
		{
			case '1':
				std::cout << "Enter number of players: ";
				std::cin >> playerCount;
				break;
			case '2':
				break;
			case '3':
				break;
			default:
				std::cout << "Please choose a correct game option";
				continue;
		}

	}

	shuffleDeck(CARDS_IN_DECK, deck);
	unsigned short playerCount;
	std::cout << "Enter player count: ";
	std::cin >> playerCount;

	Player* players = new Player[playerCount];
	dealCardsToPlayers(playerCount, CARDS_PER_PLAYER, deck, players);
	printPlayers(players, playerCount);

	//--------------------------------------
	delete[] deck;
	deck = nullptr;

	delete[] players;
	players = nullptr;

	return 0;
}