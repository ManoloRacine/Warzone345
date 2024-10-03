<<<<<<< HEAD:src/Player/PlayerDriver.cpp
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Order.h"
#include <vector>

using namespace std;

void testPlayer() {
    // Create a deck and some cards
    Deck* deck = new Deck();
    deck->generateDeck();

    // Create continents and territories
    Continent* asia = new Continent("Asia", 5);
    Territory* china = new Territory("China", { 0, 0 }, asia);
    Territory* india = new Territory("India", { 1, 0 }, asia);
    asia->addTerritory(china);
    asia->addTerritory(india);

    // Create a player
    Player* player = new Player();

    // Adding Things to the player
    player->addTerritories(china);
    player->getHand()->draw(deck);
    player->getHand()->draw(deck);

    // Issue some orders
    player->issueOrder(new Deploy());
    player->issueOrder(new Airlift());

    // To defend
    player->toDefend(player->getTerritories());

    // To Attack
    player->toAttack(asia->territories);

    // Display player information
    std::cout << player;

    // Clean up
    delete deck;
    delete player;
    delete asia;  // Deleting the continent also deletes its territories
}

int main() {
    testPlayer();
    return 0;
}
=======
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Order.h"
#include <vector>
#include "PlayerDriver.h"

using namespace std;

void testPlayer() {
   

    // Create a deck and some cards
    Deck* deck = new Deck();
    deck->generateDeck();

    // Create continents and territories
    Continent* asia = new Continent("Asia", 5);
    Continent* europe = new Continent("Europe", 4);
    Territory* china = new Territory("China", { 0, 0 }, asia);
    Territory* india = new Territory("India", { 1, 0 }, asia);
    Territory* spain = new Territory("Spain", { 1, 1 }, europe);
    asia->addTerritory(china);
    asia->addTerritory(india);
    europe->addTerritory(spain);

    
    // Create a player
    Player* player = new Player("player1");

    // Adding Things to the player
    player->addTerritories(spain);
    player->getHand()->draw(deck);
    player->getHand()->draw(deck);

    // Issue some orders
    player->issueOrder(new Deploy());
    player->issueOrder(new Airlift());

    // To defend
    player->toDefend(player->getTerritories());

    // To Attack
    player->toAttack(asia->getTerritories());

    // Display player information
    player->printPlayer();

    // Clean up
    delete deck;
    delete player;
    delete asia;
    delete europe;
}
>>>>>>> d7486e98d6d9b9a6fbac2618f3925d86af305017:src/PlayerDriver.cpp
