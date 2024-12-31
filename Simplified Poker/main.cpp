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
#include "Validations.h"
#include "Game functions.h"

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

void printDeck(const Card* deck, const unsigned cardsCount, const char separator)
{
	for (size_t i = 0; i < cardsCount; i++)
	{
		std::cout << deck[i].type->pip << deck[i].suit->name << separator;
	}
}

void printPlayers(const Player* players, const unsigned playerCount)
{
	for (size_t i = 0; i < playerCount; i++)
	{
		printDeck(players[i].cards, 3, '\n');
		std::cout << '\n' << calculatePlayerPoints(players[i].cards) << '\n' << '\n';
	}
}

void showPlayerBalances(const Player* players, const unsigned playerCount)
{
	std::cout << '\n';

	for (size_t current = 0; current < playerCount;)
	{
		for (int row = 0; row < 3; row++)
		{
			std::cout << "Player " << ++current << ": " << players[current - 1].chips << " ";
		}

		std::cout << '\n';
	}
}

int main()
{
	char gameCommand;
	char playerAnswer;
	unsigned short playerCount = 0;
	Player* players = nullptr;
	int lastRaise = 0;

	while (true)
	{
		printGameCommands();
		std::cin >> gameCommand;
		switch (gameCommand)
		{
			case '1':
				enterPlayerCount(playerCount);
				players = new Player[playerCount];

				shuffleDeck(CARDS_IN_DECK, deck);
				dealCardsToPlayers(playerCount, CARDS_PER_PLAYER, deck, players);

				for (size_t playerIndx = 0; playerIndx < playerCount; playerIndx++)
				{
					orderPlayerCards(players[playerIndx]);
					players[playerIndx].points = calculatePlayerPoints(players[playerIndx].cards);
				}

				showPlayerBalances(players, playerCount);

				for (size_t playerIndx = 0; playerIndx < playerCount; playerIndx++)
				{
					std::cout << '\n' << "Player " << playerIndx + 1 << "\n\n";
					std::cout << "You have given: " << players[playerIndx].given << '\n';
					std::cout << "Last raise is: " << lastRaise << "\n\n";

					std::cout << "Do you want to see your cards and points?(y/n): ";

					do
					{
						std::cin >> playerAnswer;

						if (playerAnswer == 'y' || playerAnswer == 'n')
							break;

						std::cout << "Enter a valid option";
					} while (true);

					if (playerAnswer == 'y')
					{
						printDeck(players[playerIndx].cards, CARDS_PER_PLAYER, ' ');
						std::cout << " " << players[playerIndx].points << '\n';
					}

					//std::cout << "Player " << playerIndx + 1 << " do you raise, call, or fold()"

				}

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

	//printPlayers(players, playerCount);

	//--------------------------------------
	delete[] deck;
	deck = nullptr;

	delete[] players;
	players = nullptr;

	return 0;
}