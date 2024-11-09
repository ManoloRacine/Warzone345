

#include "../Orders/Order.h"
#include "../Orders/OrderDriver.h"
#include "../GameEngine/GameEngine.h"


void testOrdersLists()
{

    // Create a deck and some cards
    Deck* deck = new Deck();
    deck->generateDeck();

    // generating two players
    Player* player1 = new Player("player1");
    Player* player2 = new Player("player2");
    vector<Player*> players;
    players.push_back(player1);
    players.push_back(player2);

    //loading a map to show functionality
    MapLoader mapLoader;
    Map loadedMap;
    mapLoader.loadMap(loadedMap,"../res/maps/usa.txt");

    int playerIndex = 0;
    int totalPlayers = players.size();

    
    Continent* asia = new Continent("Asia", 5);
    Continent* europe = new Continent("Europe", 4);

    Territory* china = new Territory("China", { 0, 0 }, asia, player1, 5);
    Territory* india = new Territory("India", { 1, 0 }, asia, player2, 3);
    Territory* spain = new Territory("Spain", { 1, 1 }, europe, player1, 4);
    Territory* portugal = new Territory("portugal", { 1, 2 }, europe, player2, 2);
    Territory* england = new Territory("England", { 2, 2}, europe, player2, 4);
    
    india->addConnectedTerritory(china);
    china->addConnectedTerritory(india);
    spain->addConnectedTerritory(china);
    china->addConnectedTerritory(india);

    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);
    player1->getHand()->draw(deck);

    Advance* advance = new Advance(nullptr, nullptr, 1, nullptr, nullptr);
    Negotiate* negotiate = new Negotiate(nullptr, nullptr, 1, nullptr, nullptr);
    negotiate->validate(player1, player2);
    advance->validate(player1,1,china,india);


    

}