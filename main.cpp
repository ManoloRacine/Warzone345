#include "src/Map/MapDriver.h"
#include "src/Cards/CardsDriver.h"
#include "src/GameEngine/GameEngineDriver.h"

#define quote(x) #x

using namespace std;

#include "GameEngineDriver.h"

int main() {
    testLoadMaps();
    testCards();
    testGameStates();
    return 0;
}
