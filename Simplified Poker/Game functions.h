#pragma once
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
* <header file for helper functions that are used during the game>
*
*/

#include "Player Structures.h"
#include "Deck Structures.h"

void orderTwoCardsInPlayerHand(Card& firstCard, Card& secondCard);

void orderPlayerCards(Player& player);

unsigned short calculatePlayerPoints();

