#include "Player.h"
#include "Map.h"
#include "Order.h"
#include <iostream>

void testPlayers() {
    Player player;

    // Create some dummy territories and orders
    Territory* territory1 = new Territory("Territory 1");
    Territory* territory2 = new Territory("Territory 2");
    Territory* territory3 = new Territory("Territory 3");
    Territory* territory4 = new Territory("Territory 4");
    vector<Territory*> territories = { {territory1},{territory2} };
    vector<Territory*> territories2 = { {territory4},{territory3} };

    player.toDefend(territories).push_back(territory1);
    player.toAttack(territories2).push_back(territory2);

    Order* order1 = new Order("Deploy Order");
    player.issueOrder(order1);

    // Test player methods
    std::cout << "Territories to defend:" << std::endl;
    for (Territory* t : player.toDefend()) {
        std::cout << t->getName() << std::endl;
    }

    std::cout << "Territories to attack:" << std::endl;
    for (Territory* t : player.toAttack()) {
        std::cout << t->getName() << std::endl;
    }

    std::cout << "Orders issued:" << std::endl;
    std::cout << player << std::endl;
}

int main() {
    testPlayers();
    return 0;
}
