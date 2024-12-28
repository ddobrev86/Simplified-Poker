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


unsigned short calculatePlayerPoints()
{
	return 0;
}