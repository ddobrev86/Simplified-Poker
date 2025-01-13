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

void enterPlayerCount(unsigned short& playerCount)
{
	do
	{
		std::cout << '\n' << "Enter player count: ";
		std::cin >> playerCount;
		if (playerCount >= 2 && playerCount <= 9)
			break;

		std::cout << "Player count must be between 2 and 9!" << std::endl;
	} while (true);
}

void askPlayerAction(const Player player, const unsigned lastRaise, 
	const size_t playerIndx, char& playerAnswer)
{
	if (lastRaise < 0)
	{
		std::cout << "Invalid raise";
		return;
	}

	bool canCall = (player.given < lastRaise);

	do
	{
		if (canCall)
			std::cout << "Player " << playerIndx + 1 << " do you raise, call, or fold(r/c/f): ";
		else
			std::cout << "Player " << playerIndx + 1 << " do you raise, or fold(r/f): ";

		std::cin >> playerAnswer;

	} while (playerAnswer != 'r' && playerAnswer != 'f' && (playerAnswer != 'c' && canCall));

}