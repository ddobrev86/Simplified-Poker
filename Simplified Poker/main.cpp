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

const CardType CARD_TYPES[TYPES_COUNT] = {
	{"7", 7},
	{"8", 8},
	{"9", 9},
	{"10", 10},
	{"J", 10},
	{"D", 10},
	{"K", 10},
	{"A", 11}
};

const CardSuit SUITS[SUITS_COUNT] = {
	{'C', 1},
	{'D', 2},
	{'H', 3},
	{'S', 4},
};

Card* deck = fillDeckWithCards(CARD_TYPES, SUITS, TYPES_COUNT, SUITS_COUNT, CARDS_IN_DECK);

int main()
{
	char gameCommand;
	unsigned short playerCount = 0;
	Player* players = nullptr;
	unsigned short inGame;

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

				playGame(players, playerCount, deck, CARDS_IN_DECK, inGame);

				break;
			case '2':
				if (!getGameInfo(players, playerCount, inGame))
				{
					system("cls");
					std::cout << "Cound not load game\n";
					break;
				}

				playGame(players, playerCount, deck, CARDS_IN_DECK, inGame);

				break;
			case '3':
				closeProgram = true;
				break;
			default:
				std::cout << '\n' << "Please choose a correct game option" << '\n';
				continue;
		}

	}

	//--------------------------------------
	delete[] deck;
	deck = nullptr;

	return 0;
}