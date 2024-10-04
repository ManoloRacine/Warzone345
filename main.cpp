#include "src/Map/MapDriver.h"
#include "src/Cards/CardsDriver.h"
#include "src/GameEngine/GameEngineDriver.h"
#include "src/Orders/OrdersDriver.h"


int main() {
    testLoadMaps();
    testCards();
    testGameStates();
    testOrdersLists();
    return 0;
}
