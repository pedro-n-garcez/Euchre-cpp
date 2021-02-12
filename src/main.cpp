#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>
#include <random>

enum Suit { Spades, Diamonds, Hearts, Clubs };
enum Rank {A=14,K=13,Q=12,J=11,T=10,N=9};

class Card{
	public:
		Rank rank;
		Suit suit;
		Card(Suit s, Rank r){
			rank = r;
			suit = s;
		}
		std::string ReturnSuitString()
		{
			switch(suit){
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
					return "No suit found";
					break;
			}
		}
		std::string ReturnRankString()
		{
			switch(rank){
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
					return "Joker";
					break;
				case T:
					return "Ten";
					break;
				case N:
					return "Nine";
					break;
				default:
					return "No rank found";
					break;
			}
		}
};

class Player{
	private:
		std::stack<Card*> myCards;
		std::string name;
	public:
		Player(){}
		void addCard(Card * c){
			myCards.push(c);
		}
		
};

class Game{
	private:
		bool isPlaying;
		std::vector<Card*> v_deck;
	public:
		Player p1, p2, p3, p4;
		std::stack<Card*> Deck;
		void CreateDeck()
		{
			//add the 24 cards to vector
			v_deck.push_back(new Card(Spades,A));
			v_deck.push_back(new Card(Spades,K));
			v_deck.push_back(new Card(Spades,Q));
			v_deck.push_back(new Card(Spades,J));
			v_deck.push_back(new Card(Spades,T));
			v_deck.push_back(new Card(Spades,N));
			v_deck.push_back(new Card(Diamonds,A));
			v_deck.push_back(new Card(Diamonds,K));
			v_deck.push_back(new Card(Diamonds,Q));
			v_deck.push_back(new Card(Diamonds,J));
			v_deck.push_back(new Card(Diamonds,T));
			v_deck.push_back(new Card(Diamonds,N));
			v_deck.push_back(new Card(Hearts,A));
			v_deck.push_back(new Card(Hearts,K));
			v_deck.push_back(new Card(Hearts,Q));
			v_deck.push_back(new Card(Hearts,J));
			v_deck.push_back(new Card(Hearts,T));
			v_deck.push_back(new Card(Hearts,N));
			v_deck.push_back(new Card(Clubs,A));
			v_deck.push_back(new Card(Clubs,K));
			v_deck.push_back(new Card(Clubs,Q));
			v_deck.push_back(new Card(Clubs,J));
			v_deck.push_back(new Card(Clubs,T));
			v_deck.push_back(new Card(Clubs,N));
			//shuffle vector
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::shuffle(v_deck.begin(), v_deck.end(), std::default_random_engine(seed));
			//create stack
			for (int i = 0; i < 24; i++){
				Deck.push(v_deck[i]);
			}
		}
		void Start()
		{
			isPlaying = true;
			while (isPlaying)
			{
				p1.addCard(Deck.top());
				Deck.pop();
				p2.addCard(Deck.top());
				Deck.pop();
				p3.addCard(Deck.top());
				Deck.pop();
				p4.addCard(Deck.top());
				Deck.pop();
			
				Card * topCard = Deck.top();
				std::cout << "The top card on the deck is " << topCard->ReturnRankString() << " of " << topCard->ReturnSuitString() << "." << std::endl;
				std::cout << "There are now " << Deck.size() << " cards on the deck." << std::endl;
				
				isPlaying = false;
			}
		}
};

int main()
{
	Game g;
	g.CreateDeck();
	g.Start();
	return 0;
}
