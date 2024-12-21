#pragma once

struct CardType
{
	const char pip[3];
	unsigned short value;
};

struct Card
{
	char suit;
	const CardType* type;
};

