#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>
#include <random>

const float minWeight = 0.65f;

enum Suit { Diamonds=1, Clubs=2, Hearts=3, Spades=4 };
enum Rank {A=14,K=13,Q=12,J=11,T=10,N=9};

class Card{
	public:
		Rank rank;
		Suit suit;
		int value;
		Card(Suit s, Rank r){
			rank = r;
			suit = s;
			value = r;
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
					return "Suit not found";
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
};

class Player{
	private:
		std::vector<Card*> myCards;
		int playerNumber;
	public:
		Player(int n){playerNumber = n;}
		void addCard(std::vector<Card*> * v){
			myCards.push_back(v->front());
			v->erase(v->begin());
		}
		std::string ReturnPlayerNumber(){
			return "Player " + std::to_string(playerNumber);
		}
		void PrintHand(){
			std::cout << ReturnPlayerNumber() << " has the following hand: " << std::endl;
			for(size_t i = 0; i<myCards.size();i++){
				std::cout << myCards[i]->ReturnRankString() << " of " << myCards[i]->ReturnSuitString() << std::endl; 
			}
		}
		void ClearHand(){
			 myCards.clear();
		}
		Card * playCard(int pos){
			Card * c = myCards[pos];
			myCards.erase(myCards.begin()+pos);
			return c;
		}
		
		//distribute points for a card given trump suit
		int evaluateCard(Card * c, Suit trump){
			int card_value = c->value;
			if (c->suit == trump && c->rank == J){
				card_value += 20;
			} else if (c->rank == J && c->suit % 2 == trump % 2 ){
				card_value += 19;
			} else if (c->suit == trump && c->rank != J){
				card_value += 10;
			} return card_value;
		}
		
		//adds points of all player's cards and returns a weight for hand
		float handWeight(Suit trump){
			float total = 0.0f;
			for (size_t i = 0; i < myCards.size(); i++){
				total += evaluateCard(myCards[i],trump);
			} return total / 130.0f;
		}
		bool wantTrump(float weight){
			if (weight >= minWeight){
				return true;
			}
			return false;
		}
		
};

class Game{
	private:
		bool isPlaying;
	public:
		std::vector<Player*> players;
		Player * p1=new Player(1);
		Player * p2=new Player(2);
		Player * p3=new Player(3);
		Player * p4=new Player(4);
		Card * trump;
		std::vector<Card*> Deck;

		Game(){
			players.push_back(p1);
			players.push_back(p2);
			players.push_back(p3);
			players.push_back(p4);
		}

		void CreateDeck()
		{
			//add the 24 cards to vector
			Deck.push_back(new Card(Spades,A));
			Deck.push_back(new Card(Spades,K));
			Deck.push_back(new Card(Spades,Q));
			Deck.push_back(new Card(Spades,J));
			Deck.push_back(new Card(Spades,T));
			Deck.push_back(new Card(Spades,N));
			Deck.push_back(new Card(Diamonds,A));
			Deck.push_back(new Card(Diamonds,K));
			Deck.push_back(new Card(Diamonds,Q));
			Deck.push_back(new Card(Diamonds,J));
			Deck.push_back(new Card(Diamonds,T));
			Deck.push_back(new Card(Diamonds,N));
			Deck.push_back(new Card(Hearts,A));
			Deck.push_back(new Card(Hearts,K));
			Deck.push_back(new Card(Hearts,Q));
			Deck.push_back(new Card(Hearts,J));
			Deck.push_back(new Card(Hearts,T));
			Deck.push_back(new Card(Hearts,N));
			Deck.push_back(new Card(Clubs,A));
			Deck.push_back(new Card(Clubs,K));
			Deck.push_back(new Card(Clubs,Q));
			Deck.push_back(new Card(Clubs,J));
			Deck.push_back(new Card(Clubs,T));
			Deck.push_back(new Card(Clubs,N));
			//shuffle vector
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::shuffle(Deck.begin(), Deck.end(), std::default_random_engine(seed));
		}

		void Start()
		{
			isPlaying = true;
			while (isPlaying)
			{
				for (size_t i = 0; i < players.size(); i++){
					players[i]->addCard(&Deck);
					players[i]->addCard(&Deck);
				}
				
				for (size_t j = 0; j < players.size(); j++){
					players[j]->addCard(&Deck);
					players[j]->addCard(&Deck);
					players[j]->addCard(&Deck);										
				}
			
				std::cout << "The top card on the deck is " << Deck.front()->ReturnRankString() << " of " << Deck.front()->ReturnSuitString() << "." << std::endl;
				std::cout << "There are now " << Deck.size() << " cards on the deck." << std::endl;
				std::cout << "Will " << Deck.front()->ReturnSuitString() << " be trump?\n" << std::endl;
				
				Player * choseTrump;
				bool trumpChosen = false;
				
				//TEST AREA - FOR DEBUGGING ONLY!!
				for (size_t a=0; a < players.size();a++){
					players[a]->PrintHand();
					std::cout << players[a]->handWeight(Deck.front()->suit) << std::endl;
					std::cout << "Trump candidate is: " + Deck.front()->ReturnSuitString() << std::endl << "\n";
				}
				
				//if player's hand is strong enough given the trump candidate, they will order it up
				for (size_t k = 0; k < players.size(); k++){
					if (players[k]->wantTrump(players[k]->handWeight(Deck.front()->suit)) == true){
						choseTrump = players[k];
						std::cout << players[k]->ReturnPlayerNumber() << " says yes!" << std::endl;
						trumpChosen = true;
						trump = Deck.front();
						break;
					} else{
						std::cout << players[k]->ReturnPlayerNumber() << " says no." << std::endl;						
					}
				}
				
				if(trumpChosen == false)
				{
					std::cout << "\n" << "Nobody wanted " << Deck.front()->ReturnSuitString() << " as Trump, so next player gets to choose." << std::endl;
 					for (size_t m = 0; m < players.size(); m++){
						for (int s = 1; s < 5; s++){
							if (players[m]->wantTrump(players[m]->handWeight(static_cast<Suit>(s))) == true){
								choseTrump = players[m];
								trump = new Card(static_cast<Suit>(s),A);
								trumpChosen = true;
								break;
							}
						}
						if (trumpChosen == true){
							break;
						}
						std::cout << players[m]->ReturnPlayerNumber() << " pass. " << std::endl;
					}
				}
				
				//if no trump was chosen, cards are redealt
				if(trumpChosen == false){
					std::cout << "\n" << "Bust! Redealing..." << std::endl;
					Deck.clear();
					for (size_t n=0;n<players.size();n++){
						players[n]->ClearHand();
					}
					CreateDeck();
					Start();
				}
				
				std::cout << "\n" << choseTrump->ReturnPlayerNumber() << " chose " << trump->ReturnSuitString() << " to be trump." << std::endl;
				
				isPlaying = false;
			}
		}
};

int main()
{
	Game g;
	g.CreateDeck();
	g.Start();
}
