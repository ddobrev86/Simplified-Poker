#include "Game functions.h"
#include "Initialisation Functions.h"
#include <iostream>

const unsigned short SEVEN_OF_CLUBS_POINTS = 11;
const unsigned short TWO_ACES_POINTS = 22;
const unsigned short TWO_SEVENS_POINTS = 23;
const unsigned short THREE_SEVENS_POINTS = 34;

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

bool isSevenOfClubs(const Card card)
{
	return card.type->value == 7 && card.suit->name == 'C';
}

short sumCardValues(const Card* playerCards, size_t startIndex)
{
	if (!playerCards || startIndex < 0 || startIndex > 1)
		return -1;

	short sum = 0;
	for (size_t indx = startIndex; indx < CARDS_PER_PLAYER; indx++)
	{
		sum += playerCards[indx].type->value;
	}

	return (sum == 21 ? THREE_SEVENS_POINTS : sum);
}

short countIdenticalCardTypes(const Card* playerCards, size_t startIndex)
{
	if (!playerCards || startIndex < 0 || startIndex > 1)
		return -1;

	size_t endIndex = startIndex + 1;
	unsigned short count = 0;

	while (startIndex < endIndex)
	{
		if (playerCards[startIndex].type->pip == playerCards[endIndex].type->pip)
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

short countIdenticalCardSuits(const Card* playerCards, size_t startIndex)
{
	if (!playerCards || startIndex < 0 || startIndex > 1)
		return -1;

	size_t endIndex = startIndex + 1;
	unsigned short count = 0;

	while (startIndex < endIndex)
	{
		if (playerCards[startIndex].suit->value == playerCards[endIndex].suit->value)
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

unsigned short calculatePlayerPoints(const Card* playerCards)
{
	if (!playerCards)
		return 0;

	bool playerHasSevenOfClubs = isSevenOfClubs(playerCards[0]);
	short identicalTypes;
	short identicalSuits;

	unsigned short points = 0;
	unsigned short currentPoints = 0;

	identicalTypes = countIdenticalCardTypes(playerCards, playerHasSevenOfClubs) + playerHasSevenOfClubs;
	identicalSuits = countIdenticalCardSuits(playerCards, playerHasSevenOfClubs) + playerHasSevenOfClubs;

	bool hasTwoSevens = (identicalTypes && playerCards[1].type->value == 7);
	bool hasTwoAces = (playerCards[1].type->value == 11 && identicalTypes);

	if (identicalTypes > 1 || identicalSuits > 1)
	{
		points = sumCardValues(playerCards, playerHasSevenOfClubs);
	}
	else if (!playerHasSevenOfClubs && hasTwoSevens)
	{
		points = TWO_SEVENS_POINTS;
	}
	else if (hasTwoAces)
	{
		points = TWO_ACES_POINTS;
	}
	else
	{
		points = playerCards[CARDS_PER_PLAYER - 1].type->value;
	}

	if (playerHasSevenOfClubs && !hasTwoSevens)
		points += SEVEN_OF_CLUBS_POINTS;

	return points;
}