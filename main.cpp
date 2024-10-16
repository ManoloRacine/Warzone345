#include "src/Map/MapDriver.h"
#include "src/Cards/CardsDriver.h"
#include "src/GameEngine/GameEngineDriver.h"
#include "src/Orders/OrderDriver.h"
#include "src/Player/PlayerDriver.h"
#include <iostream>

#include "Command/Command.h"
#include "CommandProcessing/CommandProcessor.h"
using namespace std;


int main() {
    CommandProcessor commandProcessor;
    GameEngine gameEngine;
    Command* command = commandProcessor.getCommand(&gameEngine);
    cout << command->getCommand() << endl;
    cout << command->getType() << endl;
    return 0;
}
