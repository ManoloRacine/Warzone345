#include "src/Map/MapDriver.h"
#include "src/Cards/CardsDriver.h"
#include "src/GameEngine/GameEngineDriver.h"
#include "src/Orders/OrderDriver.h"
#include "src/Player/PlayerDriver.h"
#include <iostream>
#include "src/CommandProcessing/CommandProcessingDriver.h"
#include "src/Logger/ LoggingObserverDriver.h"

#include "Command/Command.h"
#include "CommandProcessing/CommandProcessor.h"
using namespace std;


int main() {
    cout << "-----------------------------testLoggingObserver()-----------------------------------" << std::endl;
    //testLoggingObserver();
    cout << "-----------------------------testCommandProcessor()-----------------------------------" << std::endl;
    //testCommandProcessor();

    // FileCommandProcessorAdapter commandProcessor("../res/CommandFiles/test.txt");
    // GameEngine gameEngine;
    // Command* command = commandProcessor.getCommand(&gameEngine);
    // cout << command->getCommand() << endl;
    // cout << command->getType() << endl;

    cout << "-----------------------------testStartupPhase()-----------------------------------" << std::endl;
    //testStartupPhase();
    cout << "-----------------------------testMainGameLoop()-----------------------------------" << std::endl;
    testMainGameLoop();
    cout << "-----------------------------testOrdersLists()-----------------------------------" << std::endl;
    //testOrdersLists();


    return 0;
}
