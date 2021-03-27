#include "Card.hpp"
#include "Player.hpp"
#include <tuple>
#include <chrono>
#include <algorithm>
#include <random>

class Game {
private:
	bool isPlaying;
public:
	std::vector<Player*> players;
	Player * p1 = new Player(0);
	Player * p2 = new Player(1);
	Player * p3 = new Player(2);
	Player * p4 = new Player(3);
	Card * trump;
	std::vector<Card*> Deck;
	std::vector<std::tuple<Card*, int>> Trick;

	Game();
	void CreateDeck();
	void Start();
};
