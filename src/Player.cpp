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

int main() {
    testPlayer();
    return 0;
}
