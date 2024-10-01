#include "Player.h"
#include "Map.h"
#include "Order.h"
#include <iostream>

void testPlayers() {
    Player player;

    // Create some dummy territories and orders
    Territory* territory1 = new Territory("Territory 1");
    Territory* territory2 = new Territory("Territory 2");
    player.toDefend().push_back(territory1);
    player.toAttack().push_back(territory2);

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
