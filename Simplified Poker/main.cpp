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
#include "File Handling.h"
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
	unsigned minBalance = 0;

	size_t lastPlayerToRaise = 0;
	size_t currentPlayer = 0;
	unsigned short inGame;

	unsigned winnerCount = 0;
	unsigned maxPoints;

	size_t winnerIndx;

	bool isTie = false;

	bool closeProgram = false;

	while (!closeProgram)
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

					bettingPhase(players, currentPlayer, playerCount, playerAnswer, lastRaise, 
						pot, inGame, lastPlayerToRaise, maxBet, minBalance, isTie);

					winnerCount = 0;
					maxPoints = getMaxPoints(players, playerCount);
					getWinners(players, playerCount, maxPoints, winnerCount, winnerIndx);

					system("cls");
					printWinnersHeader(players, playerCount, pot, winnerCount);

					if (winnerCount > 1)
					{
						readyPlayersForTie(players, playerCount, inGame, pot / 2, playerAnswer,
							lastRaise, maxBet, isTie);
						continue;
					}
					else 
					{
						players[winnerIndx].chips += pot;
					}

					playAgain(playerAnswer);

					if (playerAnswer == 'n')
					{
						delete[] players;
						players = nullptr;

						break;
					}

					resetGameParams(players, currentPlayer, playerCount, lastRaise,
						pot, inGame, lastPlayerToRaise, maxBet, isTie);

					if (inGame == 1)
					{
						std::cout << "\nPlayer " << winnerIndx + 1 << " is the only player left and is the winner\n\n";
						break;
					}

				} while (true);
				

				break;
			case '2':
				if (getGameInfo(players, playerCount))
				{

				}

				break;
			case '3':
				closeProgram = true;
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

	return 0;
}