#include "Initialisation Functions.h"

Card* fillDeckWithCards(const CardType* cardTypes, const char* cardSuites, 
	const unsigned typesCount, const unsigned suitsCount, const unsigned cardsCount)
{
	Card* deck = new Card[suitsCount * typesCount];

	for (size_t currentCardType = 0; currentCardType < typesCount; currentCardType++)
	{
		for (size_t currentSuit = 0; currentSuit < suitsCount; currentSuit++)
		{
			deck->type = &cardTypes[currentCardType];
			deck->suit = cardSuites[currentSuit];
			deck++;
		}
	}

	deck -= cardsCount;

	return deck;
}