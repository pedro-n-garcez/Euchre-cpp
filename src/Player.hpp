#pragma once
#include "Card.hpp"
#include <vector>
#include <iostream>

const float minWeight = 0.65f;

class Player {
private:
	std::vector<Card*> myCards;
	int playerNumber;
public:
	Player(int n);
	void addCard(std::vector<Card*> * v);
	std::string ReturnPlayerNumber();
	void PrintHand();
	void ClearHand();
	int evaluateCard(Card * c, Suit trump);
	float handWeight(Suit trump);
	bool wantTrump(float weight);
	int bestCardIndex(Suit trump, bool first, Suit lead);
	Card * playCard(int index, Suit trump);
};

