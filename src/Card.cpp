#include "Card.hpp"

Card::Card(Suit s, Rank r) {
	rank = r;
	suit = s;
	value = r;
}

std::string Card::ReturnSuitString() {
	switch (suit) {
	case Spades:
		return "Spades";
		break;
	case Diamonds:
		return "Diamonds";
		break;
	case Hearts:
		return "Hearts";
		break;
	case Clubs:
		return "Clubs";
		break;
	default:
		return "Suit not found";
		break;
	}
}

std::string Card::ReturnRankString()
{
	switch (rank) {
	case A:
		return "Ace";
		break;
	case K:
		return "King";
		break;
	case Q:
		return "Queen";
		break;
	case J:
		return "Jack";
		break;
	case T:
		return "Ten";
		break;
	case N:
		return "Nine";
		break;
	default:
		return "Rank not found";
		break;
	}
}