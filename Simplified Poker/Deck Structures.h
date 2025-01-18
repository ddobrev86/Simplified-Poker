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
* <header file for all structures, connected to the deck>
*
*/

#pragma once
#include <stdlib.h>

struct CardType
{
	const char pip[3];
	unsigned short value;
};

struct CardSuit
{
	const char name;
	unsigned short value;
};

struct Card
{
	const CardSuit* suit;
	const CardType* type;
};

