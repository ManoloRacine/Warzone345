#include "src/Map/MapDriver.h"
#include "src/Cards/CardsDriver.h"
#include "src/GameEngine/GameEngineDriver.h"
#include "src/Orders/OrderDriver.h"
#include "src/Player/PlayerDriver.h"
#include <iostream>
using namespace std;


int main() {
    std::cout << "\n STARTING LOAD MAPS TEST \n" << endl;
    testLoadMaps();
    std::cout << "\n STARTING CARDS TEST \n" << endl;
    testCards();
    std::cout << "\n STARTING ORDERS LISTS TEST \n" << endl;
    testOrdersLists();
    std::cout << "\n STARTING PLAYER TEST \n" << endl;
    testPlayer();
    std::cout << "\n STARTING GAME STATES TEST \n" << endl;
    testGameStates();
    return 0;
}
