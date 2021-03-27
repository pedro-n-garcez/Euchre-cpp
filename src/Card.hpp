#pragma once
#include <string>

enum Suit { None = 0, Diamonds = 1, Clubs = 2, Hearts = 3, Spades = 4 };
enum Rank { A = 14, K = 13, Q = 12, J = 11, T = 10, N = 9 };

class Card {
public:
	Rank rank;
	Suit suit;
	int value;
	Card(Suit s, Rank r);
	std::string ReturnSuitString();
	std::string ReturnRankString();
};