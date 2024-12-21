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

const unsigned TYPES_COUNT = 8;
const unsigned SUITS_COUNT = 4;
const unsigned CARDS_COUNT = TYPES_COUNT * SUITS_COUNT;

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

const char SUITS[] = {
	'C',
	'D',
	'H',
	'S'
};

const Card* deck = fillDeckWithCards(CARD_TYPES, SUITS, TYPES_COUNT, SUITS_COUNT, CARDS_COUNT);

void printDeck(const Card* deck, const unsigned CARDS_COUNT)
{
	for (size_t i = 0; i < CARDS_COUNT; i++)
	{
		std::cout << deck[i].type->pip << deck[i].suit << std::endl;
	}
}

int main()
{
	printDeck(deck, CARDS_COUNT);

	return 0;
}