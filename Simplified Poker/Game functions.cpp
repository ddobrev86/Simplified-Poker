#include "Game functions.h"
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

	return (sum == 21 || sum == 14 ? THREE_SEVENS_POINTS : sum);
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
	else if (hasTwoSevens)
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

unsigned calculateMinPlayerBalance(const Player* players, const unsigned short playerCount)
{
	if (!players)
		return 0;

	unsigned min = CHIP_VALUE * STARTING_CHIP_COUNT;

	for (size_t indx = 0; indx < playerCount; indx++)
	{
		if (players[indx].isActive && players[indx].chips < min && !players[indx].allIn)
		{
			min = players[indx].chips;
		}
	}

	return min;
}

void raise(Player& player, const Player* allPlayers,
	const unsigned short playerCount, unsigned& lastRaise, 
	unsigned& pot, unsigned& maxBet, const unsigned minBalance)
{
	if (!allPlayers)
	{
		return;
	}

	//unsigned minBalance = calculateMinPlayerBalance(allPlayers, playerCount);

	unsigned raise;
	bool belowMin = false;
	bool overLastRaise = false;

	char allInAnswer;

	do
	{
		std::cout << "\nEnter your raise: ";
		std::cin >> raise;

		belowMin = (raise <= minBalance);
		overLastRaise = (lastRaise + CHIP_VALUE <= raise);

		if (!belowMin && minBalance != player.chips)
		{
			std::cout << "Raise shouldn't exceed the min player balance(" << minBalance << ")" << std::endl;
			continue;
		}

		if (!overLastRaise)
		{
			std::cout << "Raise should be at least " << lastRaise + CHIP_VALUE << std::endl;
			continue;
		}

		if (raise >= player.chips)
		{
			askToGoAllIn(allInAnswer);

			if (allInAnswer == 'y')
			{
				player.allIn = true;
				raise = player.chips;
				break;
			}

			continue;
		}

	} while (!(belowMin && overLastRaise));

	//unsigned toGive = raise - player.given;

	player.chips -= raise;
	player.given += raise;

	pot += raise;

	lastRaise = raise;
	maxBet = player.given;
}

void call(Player& player, unsigned& maxBet, unsigned& pot)
{
	unsigned toGive = maxBet - player.given;

	player.chips -= toGive;
	player.given += toGive;

	pot += toGive;

}

void fold(Player& player)
{
	player.isActive = false;
}

void playPlayerAction(Player* players, const size_t currentPlayer, 
	const unsigned short playerCount, const char playerAnswer, unsigned& lastRaise,
	unsigned& pot, unsigned short& inGame, size_t& lastPlayerToRaise, unsigned& maxBet,
	const unsigned minBalance)
{
	switch (playerAnswer)
	{
		case 'r':
			raise(players[currentPlayer], players, playerCount, 
				lastRaise, pot, maxBet, minBalance);

			lastPlayerToRaise = currentPlayer;
			break;
		case 'c':
			call(players[currentPlayer], maxBet, pot);
			break;
		case 'f':
			fold(players[currentPlayer]);
			inGame--;
			break;
	}
}

unsigned getMaxPoints(const Player* players, const unsigned short playerCount)
{
	if (!players)
	{
		return 0;
	}

	unsigned maxPoints = 0;

	for (size_t indx = 0; indx < playerCount; indx++)
	{
		if (players[indx].isActive && players[indx].points > maxPoints)
		{
			maxPoints = players[indx].points;
		}
	}

	return maxPoints;
}

void getWinners(Player* players, const unsigned short playerCount, 
	const unsigned maxPoints,
	unsigned& winnerCount, size_t& winnerIndx)
{
	if (!players)
	{
		return;
	}

	for (size_t indx = 0; indx < playerCount; indx++)
	{
		if (players[indx].isActive)
		{
			if (players[indx].points == maxPoints)
			{
				winnerCount++;
				winnerIndx = indx;
			}
			else
			{
				players[indx].isActive = false;
			}
		}
	}
}