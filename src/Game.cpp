#include "Game.hpp"

Game::Game() {
	players.push_back(p1);
	players.push_back(p2);
	players.push_back(p3);
	players.push_back(p4);
}

void Game::CreateDeck()
{
	//add the 24 cards to vector
	Deck.push_back(new Card(Spades, A));
	Deck.push_back(new Card(Spades, K));
	Deck.push_back(new Card(Spades, Q));
	Deck.push_back(new Card(Spades, J));
	Deck.push_back(new Card(Spades, T));
	Deck.push_back(new Card(Spades, N));
	Deck.push_back(new Card(Diamonds, A));
	Deck.push_back(new Card(Diamonds, K));
	Deck.push_back(new Card(Diamonds, Q));
	Deck.push_back(new Card(Diamonds, J));
	Deck.push_back(new Card(Diamonds, T));
	Deck.push_back(new Card(Diamonds, N));
	Deck.push_back(new Card(Hearts, A));
	Deck.push_back(new Card(Hearts, K));
	Deck.push_back(new Card(Hearts, Q));
	Deck.push_back(new Card(Hearts, J));
	Deck.push_back(new Card(Hearts, T));
	Deck.push_back(new Card(Hearts, N));
	Deck.push_back(new Card(Clubs, A));
	Deck.push_back(new Card(Clubs, K));
	Deck.push_back(new Card(Clubs, Q));
	Deck.push_back(new Card(Clubs, J));
	Deck.push_back(new Card(Clubs, T));
	Deck.push_back(new Card(Clubs, N));
	//shuffle vector
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(Deck.begin(), Deck.end(), std::default_random_engine(seed));
}

void Game::Start()
{
	isPlaying = true;
	while (isPlaying)
	{
		for (size_t i = 0; i < players.size(); i++) {
			players[i]->addCard(&Deck);
			players[i]->addCard(&Deck);
		}

		for (size_t j = 0; j < players.size(); j++) {
			players[j]->addCard(&Deck);
			players[j]->addCard(&Deck);
			players[j]->addCard(&Deck);
		}

		std::cout << "The top card on the deck is " << Deck.front()->ReturnRankString() << " of " << Deck.front()->ReturnSuitString() << "." << std::endl;
		std::cout << "There are now " << Deck.size() << " cards on the deck." << std::endl;
		std::cout << "Will " << Deck.front()->ReturnSuitString() << " be trump?\n" << std::endl;

		Player * choseTrump = NULL;
		bool trumpChosen = false;

		//if player's hand is strong enough given the trump candidate, they will order it up
		for (size_t k = 0; k < players.size(); k++) {
			if (players[k]->wantTrump(players[k]->handWeight(Deck.front()->suit)) == true) {
				choseTrump = players[k];
				std::cout << players[k]->ReturnPlayerNumber() << " says yes!" << std::endl;
				trumpChosen = true;
				trump = Deck.front();
				break;
			}
			else {
				std::cout << players[k]->ReturnPlayerNumber() << " says no." << std::endl;
			}
		}

		if (trumpChosen == false)
		{
			std::cout << "\n" << "Nobody wanted " << Deck.front()->ReturnSuitString() << " as Trump, so next player gets to choose." << std::endl;
			for (size_t m = 0; m < players.size(); m++) {
				for (int s = 1; s < 5; s++) {
					if (players[m]->wantTrump(players[m]->handWeight(static_cast<Suit>(s))) == true) {
						choseTrump = players[m];
						trump = new Card(static_cast<Suit>(s), A);
						trumpChosen = true;
						break;
					}
				}
				if (trumpChosen == true) {
					break;
				}
				std::cout << "\n" << players[m]->ReturnPlayerNumber() << " passes. " << std::endl;
			}
		}

		//if no trump was chosen, cards are redealt
		if (trumpChosen == false) {
			std::cout << "\n" << "Bust! Redealing..." << std::endl;
			Deck.clear();
			for (size_t n = 0; n < players.size(); n++) {
				players[n]->ClearHand();
			}
			CreateDeck();
			Start();
		}

		std::cout << "\n" << choseTrump->ReturnPlayerNumber() << " chose " << trump->ReturnSuitString() << " to be trump.\n" << std::endl;

		//Gameplay begins
		int tricksLeft = 5;
		int next = 0;
		Suit lead=None;

		while (tricksLeft != 0)
		{
			int playersLeftInTrick = 4;
			bool first = true;
			while (playersLeftInTrick != 0)
			{
				//push back a tuple with the player's card and the number of the player
				Trick.push_back(std::make_tuple(players[next]->playCard(players[next]->bestCardIndex(trump->suit, first, lead), trump->suit), next));
				std::cout << players[next]->ReturnPlayerNumber() << " played the " << std::get<0>(Trick.back())->ReturnRankString() << " of " << std::get<0>(Trick.back())->ReturnSuitString() << "." << std::endl;
				if (first) { lead = std::get<0>(Trick.back())->suit; }
				first = false;
				next = (next + 1) % 4;
				playersLeftInTrick--;
			}

			int max = 0;
			//determine player with highest card
			for (size_t i = 0; i < Trick.size(); i++) {
				if (std::get<0>(Trick[i])->value>max) {
					max = std::get<0>(Trick[i])->value;
					next = std::get<1>(Trick[i]);
				}
			}

			std::cout << "\n" << "Player " << next + 1 << " wins this trick.\n" << std::endl;

			//clear trick to start over
			Trick.clear();
			tricksLeft--;
		}

		std::cout << "\n" << "No more tricks left! Final score to be determined." << std::endl;

		isPlaying = false;
	}
}