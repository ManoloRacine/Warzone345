#include "Order.h"
#include "OrderDriver.h"
#include "GameEngine/GameEngine.h"

void testOrdersLists()
{
    auto gameEngine = new GameEngine;
    auto player = new Player(gameEngine, new Hand());
    gameEngine->addPlayer(player);

    auto orderList = player->getOrdersListObject();

    std::cout << "> Order Addition" << std::endl;

    orderList->add(UserInputOrder::create("Deploy"));
    orderList->add(UserInputOrder::create("Advance"));
    orderList->add(UserInputOrder::create("Bomb"));
    orderList->add(UserInputOrder::create("Blockade"));
    orderList->add(UserInputOrder::create("Airlift"));
    orderList->add(UserInputOrder::create("Negotiate"));

    std::cout << "> move with 2 & remove 2" << std::endl;
    orderList->move(4, 2);
    orderList->remove(2);

    auto list = *orderList->getList();
    std::cout << "> Order validation" << std::endl;
    std::cout << "> Example: first order valid? " << (orderList->getList()->at(0)->validate() ? "True": "False") << endl;

    std::cout << "> List order execution" << std::endl;
    orderList->execute();
}