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
#include <stdlib.h>

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

int main()
{
	char gameCommand;
	char playerAnswer;
	unsigned short playerCount = 0;
	Player* players = nullptr;

	unsigned lastRaise = 0;
	unsigned pot = 0;
	unsigned maxBet = 0;

	size_t lastPlayerToRaise = 0;
	size_t currentPlayer = 0;
	unsigned short inGame;

	unsigned winnerCount = 0;
	unsigned maxPoints;

	size_t winnerIndx;

	while (true)
	{
		printGameCommands();
		std::cin >> gameCommand;
		switch (gameCommand)
		{
			case '1':
				enterPlayerCount(playerCount);
				inGame = playerCount;

				players = new Player[playerCount];

				do
				{
					shuffleDeck(CARDS_IN_DECK, deck);
					dealCardsToPlayers(playerCount, CARDS_PER_PLAYER, deck, players);

					finalisePlayerDecks(players, playerCount, pot);
					do
					{
						//compiler throws a warning for players[currentPlayer]
						if (currentPlayer >= playerCount)
							break;

						if (!players[currentPlayer].isActive || players[currentPlayer].allIn)
						{
							currentPlayer++;
							currentPlayer %= playerCount;
							continue;
						}
						system("cls");

						showPlayerBalances(players, playerCount);
						printPlayerInfo(players, currentPlayer, pot, lastRaise, maxBet);
						askPlayerToPrintDeck(players[currentPlayer], playerAnswer);

						askPlayerAction(players[currentPlayer], maxBet, currentPlayer, playerAnswer);
						playPlayerAction(players, currentPlayer, playerCount, 
							playerAnswer, lastRaise, pot, inGame, lastPlayerToRaise, maxBet);

						if (inGame == 1)
						{
							break;
						}

						currentPlayer++;
						currentPlayer %= playerCount;

					} while (lastPlayerToRaise != currentPlayer);

					winnerCount = 0;
					maxPoints = getMaxPoints(players, playerCount);
					getWinners(players, playerCount, maxPoints, winnerCount, winnerIndx);

					system("cls");

					std::cout << "Pot: " << pot << '\n';
					std::cout << ((winnerCount > 1) ? ("\nIT'S A TIE!\n") : ("\nWinner is : "));
					printWinners(players, playerCount);

					if (winnerCount > 1)
					{
						readyPlayersForTie(players, playerCount, inGame, pot / 2);
						continue;
					}
					else 
					{
						players[winnerIndx].chips += pot;
					}

					playAgain(playerAnswer);

					if (playerAnswer == 'n')
					{
						break;
					}

					resetGameParams(players, currentPlayer, playerCount, lastRaise,
						pot, inGame, lastPlayerToRaise, maxBet);

				} while (true);
				

				break;
			case '2':
				break;
			case '3':
				break;
			default:
				std::cout << '\n' << "Please choose a correct game option" << '\n';
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