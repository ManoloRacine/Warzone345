#include "src/Map/MapDriver.h"
#include "src/Cards/CardsDriver.h"
#include "src/GameEngine/GameEngineDriver.h"
#include "src/Orders/OrderDriver.h"
#include "src/Player/PlayerDriver.h"


int main() {
    testLoadMaps();
    testCards();
    testOrdersLists();
    testPlayer();
    testGameStates();
    return 0;
}
