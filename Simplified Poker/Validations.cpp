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
* <file with definitions for functions that validate user input>
*
*/

#include <iostream>
#include "Validations.h"

void askPlayerYesOrNo(char& playerAnswer)
{
	do
	{
		std::cin >> playerAnswer;

		if (playerAnswer == 'n' || playerAnswer == 'y')
			return;

		//system("cls");
		std::cout << "Please choose a valid option (y/n): ";
	} while (true);
}

void enterPlayerCount(unsigned short& playerCount)
{
	do
	{
		std::cout << '\n' << "How many players are going to play (2-9)?: ";
		std::cin >> playerCount;
		if (playerCount >= 2 && playerCount <= 9)
			break;

		system("cls");
		std::cout << "Player count must be between 2 and 9";
	} while (true);
}

void fillPlayerOptions(char* playerOptions, const size_t optionsSize, 
	const bool canRaise, const bool canCall)
{
	for (size_t indx = 0; indx < optionsSize - 2; indx++)
	{
		if (indx % 2 == 1)
		{
			playerOptions[indx] = '/';
			continue;
		}

		if (canRaise && indx == 0)
		{
			playerOptions[indx] = 'r';
			continue;
		}

		if (canCall)
		{
			playerOptions[indx] = 'c';
		}
	}

	playerOptions[optionsSize - 2] = 'f';
	playerOptions[optionsSize - 1] = '\0';
}

void askPlayerAction(const Player player, const unsigned maxBet, 
	const size_t playerIndx, char& playerAnswer, const Player* players, 
	const unsigned short playerCount, const unsigned lastRaise, 
	unsigned& minBalance)
{
	if (maxBet < 0)
	{
		std::cout << "Invalid input";
		return;
	}

	minBalance = calculateMinPlayerBalance(players, playerCount);

	bool canCall = (player.given < maxBet);
	bool canRaise = (lastRaise + CHIP_VALUE <= minBalance 
		&& countActiveOrNotAllInPlayers(players, playerCount) > 1);

	/*
	array of chars, that stores the options that the player can choose from;
	2 * canRaise -> needed space for r/
	2 * canCall -> needed space for c/
	+2 -> player can fold(f) any time and one symbol for \0
	*/

	size_t optionsSize = 2 * canRaise + 2 * canCall + 2;
	char* playerOptions = new char[optionsSize];

	fillPlayerOptions(playerOptions, optionsSize, canRaise, canCall);

	do
	{
		if (!canCall && !canRaise)
		{
			std::cout << "\nPlayer " << playerIndx + 1 << " do you want "
				"to fold or not (y/n): ";

			askPlayerYesOrNo(playerAnswer);
			if (playerAnswer == 'y')
			{
				playerAnswer = 'f';
				break;
			}
		}
		else
		{
			std::cout << "\nPlayer " << playerIndx + 1 << " do you" <<
				(canRaise ? " raise" : "") << (canCall ? " call" : "") << " or fold ("
				<< playerOptions << "): ";
		}
		

		std::cin >> playerAnswer;

		if (playerAnswer == 'f' || (canRaise? playerAnswer == 'r' : false) || (canCall ? playerAnswer == 'c' : false))
		{
			break;
		}
		//system("cls");
		std::cout << "Please choose a valid option\n";

	} while (true);

	delete[] playerOptions;
	playerOptions = nullptr;

}

void askPlayerToPrintDeck(const Player player, char& playerAnswer)
{
	std::cout << "\nDo you want to see your cards and points?(y/n): ";

	askPlayerYesOrNo(playerAnswer);

	if (playerAnswer == 'y')
	{
		printDeck(player.cards, CARDS_PER_PLAYER, ' ');
		std::cout << " " << player.points << '\n';
	}
		
}

void askToGoAllIn(char& playerAnswer)
{
	std::cout << "You don't have enough chips for this bet. Do you want "
		"to go all-in?(y/n): ";

	askPlayerYesOrNo(playerAnswer);
}

void playAgain(char& playerAnswer)
{
	std::cout << "Do you want to play again?(y/n): ";
	askPlayerYesOrNo(playerAnswer);
}

void askPlayerToJoinTie(Player& player, const size_t indx, 
	const unsigned pot, unsigned short& inGame, char& playerAnswer)
{
	std::cout << "Player " << indx + 1 << " do you want to join the TIE? "
		"You have to pay " << pot << " (y/n): ";

	askPlayerYesOrNo(playerAnswer);

	if (playerAnswer == 'y')
	{
		player.chips -= pot;
		player.isActive = true;
		inGame++;
	}
}