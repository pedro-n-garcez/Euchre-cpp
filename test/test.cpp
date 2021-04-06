#include <gtest/gtest.h>
#include "../src/Game.hpp"

TEST(CardRankSuitTest, NotFound) {
    Card * card = new Card(None,A);
    EXPECT_EQ("Suit not found",card->ReturnSuitString());
    EXPECT_EQ("Ace",card->ReturnRankString());
}

TEST(HandWeightTest, LessThanOne){
    Game game;
    for (size_t i = 0; i < game.players.size(); i++){
        ASSERT_LE(game.players[i]->handWeight(Diamonds), 1);
        ASSERT_LE(game.players[i]->handWeight(Spades), 1);
        ASSERT_LE(game.players[i]->handWeight(Hearts), 1);
        ASSERT_LE(game.players[i]->handWeight(Clubs), 1);
    }
}

TEST(WantTrumpTest, MinimumWeight){
    Player * player = new Player(1);
    ASSERT_TRUE(player->wantTrump(0.66f));
    ASSERT_TRUE(player->wantTrump(0.65f));
    ASSERT_FALSE(player->wantTrump(0.64f));
}

int main(int argc, char **argv)
{   
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
