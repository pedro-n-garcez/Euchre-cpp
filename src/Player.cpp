#include "Player.hpp"

Player::Player(int n) { playerNumber = n; }

std::string Player::ReturnPlayerNumber() {
	return "Player " + std::to_string(playerNumber + 1);
}

void Player::addCard(std::vector<Card*> * v){
	myCards.push_back(v->front());
	v->erase(v->begin());
}

void Player::PrintHand() {
	std::cout << ReturnPlayerNumber() << " has the following hand: " << std::endl;
	for (size_t i = 0; i<myCards.size(); i++) {
		std::cout << myCards[i]->ReturnRankString() << " of " << myCards[i]->ReturnSuitString() << std::endl;
	}
}

void Player::ClearHand() {
	myCards.clear();
}

//distribute points for a card given trump suit
int Player::evaluateCard(Card * c, Suit trump) {
	int card_value = c->value;
	if (c->suit == trump && c->rank == J) {
		card_value += 20;
	}
	else if (c->rank == J && c->suit % 2 == trump % 2) {
		card_value += 19;
	}
	else if (c->suit == trump && c->rank != J) {
		card_value += 10;
	} return card_value;
}

//adds points of all player's cards and returns a weight for hand
float Player::handWeight(Suit trump) {
	float total = 0.0f;
	for (size_t i = 0; i < myCards.size(); i++) {
		total += evaluateCard(myCards[i], trump);
	} return total / 130.0f;
}

bool Player::wantTrump(float weight) {
	return (weight >= minWeight) ? true : false;
}

//returns strongest card for player
int Player::bestCardIndex(Suit trump, bool first, Suit lead) {
	int max = evaluateCard(myCards[0], trump);
	int index = 0;
	bool hasLead = false;

	if (first) {
		for (size_t i = 0; i < myCards.size(); i++) {
			if (evaluateCard(myCards[i], trump)>max) {
				max = evaluateCard(myCards[i], trump);
				index = i;
			}
		}
	}
	else {
		size_t i = 0;
		while (i < myCards.size()) {
			if (myCards[i]->suit == lead) { hasLead = true; }
			i++;
		}
		if (hasLead) {
			size_t j = 0;
			while (j < myCards.size()) {
				if (evaluateCard(myCards[j], trump)>max && myCards[j]->suit == lead) {
					max = evaluateCard(myCards[j], trump);
					index = j;
				}
				j++;
			}
		}
		else {
			for (size_t k = 0; k < myCards.size(); k++) {
				if (evaluateCard(myCards[k], trump)>max) {
					max = evaluateCard(myCards[k], trump);
					index = k;
				}
			}
		}
	}
	return index;
}

Card * Player::playCard(int index, Suit trump) {
	Card * c = myCards[index];
	c->value = evaluateCard(c, trump);
	myCards.erase(myCards.begin() + index);
	return c;
}