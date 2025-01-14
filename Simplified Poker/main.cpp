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

int main()
{
	char gameCommand;
	char playerAnswer;
	unsigned short playerCount = 0;
	Player* players = nullptr;

	unsigned lastRaise = 0;
	unsigned pot = 0;

	size_t lastPlayerToRaise = 0;
	size_t currentPlayer = 0;

	unsigned winnerCount = 0;
	unsigned maxPoints;

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

					players[playerIndx].chips -= CHIP_VALUE;
					//players[playerIndx].given += CHIP_VALUE;
					pot += CHIP_VALUE;
				}

				showPlayerBalances(players, playerCount);

				do
				{
					//компилаторът прави проблем за players[currentPlayer]
					if (currentPlayer >= playerCount)
						break;

					if (!players[currentPlayer].isActive)
					{
						currentPlayer++;
						continue;
					}

					std::cout << '\n' << "Pot: " << pot << '\n';
					std::cout << '\n' << "Player " << currentPlayer + 1 << "\n";
					std::cout << "You have given: " << players[currentPlayer].given << '\n';
					std::cout << "Last raise is: " << lastRaise << "\n\n";

					std::cout << "Do you want to see your cards and points?(y/n): ";

					askPlayerToPrintDeck(players[currentPlayer], playerAnswer);

					askPlayerAction(players[currentPlayer], lastRaise, currentPlayer, playerAnswer);

					switch (playerAnswer)
					{
					case 'r':
						raise(players[currentPlayer], players, playerCount, lastRaise, pot);
						lastPlayerToRaise = currentPlayer;
						break;
					case 'c':
						call(players[currentPlayer], lastRaise, pot);
						break;
					case 'f':
						fold(players[currentPlayer]);
						break;
					}

					currentPlayer++;
					currentPlayer %= playerCount;

				} while (lastPlayerToRaise != currentPlayer);
				
				winnerCount = 0;
				maxPoints = getMaxPoints(players, playerCount);
				getWinners(players, playerCount, maxPoints, winnerCount);

				if (winnerCount > 1)
				{
					std::cout << '\n' << "IT'S A TIE!" << '\n';
				}
				else
				{
					std::cout << '\n' << "Winner is: ";
				}

				printWinners(players, playerCount);
				/*for (size_t playerIndx = 0; playerIndx < playerCount; playerIndx++)
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

					askPlayerAction(players[playerIndx], lastRaise, playerIndx, playerAnswer);

					switch (playerAnswer)
					{
						case 'r':
							raise(players[playerIndx], players, playerCount, lastRaise);
							break;
						case 'c':
							break;
						case 'f':
							break;
					}

				}*/

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