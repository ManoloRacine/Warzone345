//
// Created by Ryad on 2024-10-03.
//

#include "../Orders/Order.h"
#include "../Orders/OrderDriver.h"
#include "../Orders/OrderDriver.h"

void testOrdersLists()
{
    auto orderList = new OrdersList();
    std::cout << "> Order Driver - testing Orders" << std::endl;
    std::cout << std::endl;
    std::cout << "adding orders - test" << std::endl;

    orderList->add(UserInputOrder::create("Deploy"));
    orderList->add(UserInputOrder::create("Advance"));
    orderList->add(UserInputOrder::create("Bomb"));
    orderList->add(UserInputOrder::create("Blockade"));
    orderList->add(UserInputOrder::create("Airlift"));
    orderList->add(UserInputOrder::create("Negotiate"));
    std::cout << std::endl;
    std::cout << "move with 2 & remove 1" << std::endl;
    orderList->move(2, 1);
    

    orderList->remove(1);
    std::cout << std::endl;
    auto list = *orderList->getList();
    std::cout << "Order validation" << std::endl;
    bool validation = orderList->getList()->at(0)->validate();
    std::cout << "ex. is first order valid? - " << (validation ? "True" : "False");

    std::cout << "\nList order execution" << std::endl;
    orderList->execute();
    std::cout << "\n --------END of Order List Test--------\n" << std::endl;
}