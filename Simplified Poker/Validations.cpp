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

void enterPlayerCount(unsigned short& playerCount)
{
	do
	{
		std::cout << "Enter player count: ";
		std::cin >> playerCount;
		if (playerCount >= 2 && playerCount <= 9)
			break;

		std::cout << "Player count must be between 2 and 9!" << std::endl;
	} while (true);
}