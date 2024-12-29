#include "Game functions.h"
#include "Initialisation Functions.h"
#include <iostream>

void orderTwoCardsInPlayerHand(Card& firstCard, Card& secondCard) 
{
	if (firstCard.type->value > secondCard.type->value)
	{
		swapCards(firstCard, secondCard);
	}
	else if (firstCard.type->value == secondCard.type->value)
	{
		if (firstCard.suit->value > secondCard.suit->value)
		{
			swapCards(firstCard, secondCard);
		}
	}
}

void orderPlayerCards(Player& player)
{
	orderTwoCardsInPlayerHand(player.cards[0], player.cards[1]);
	orderTwoCardsInPlayerHand(player.cards[0], player.cards[2]);
	orderTwoCardsInPlayerHand(player.cards[1], player.cards[2]);
}

short countIdenticalCardTypes(Card* playerCards, size_t startIndex)
{
	if (!playerCards || startIndex < 0 || startIndex > 1)
	{
		return -1;
	}

	size_t endIndex = startIndex + 1;
	unsigned short count = 0;

	while (startIndex < endIndex)
	{
		if (playerCards[startIndex].type->value == playerCards[endIndex].type->value)
			count++;

		if (endIndex == CARDS_PER_PLAYER - 1)
		{
			startIndex++;
			continue;
		}

		endIndex++;
	}

	return count;
}

unsigned short calculatePlayerPoints()
{
	return 0;
}