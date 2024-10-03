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
    player->toAttack(asia->getTerritories());

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
