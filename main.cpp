#include "src/Map/MapDriver.h"
#include "src/Cards/CardsDriver.h"
#include "src/GameEngine/GameEngineDriver.h"
#include "src/Orders/OrderDriver.h"
#include "src/Player/PlayerDriver.h"
#include "src/Player/PlayerStrategiesDriver.h"
#include <iostream>
#include "src/CommandProcessing/CommandProcessingDriver.h"
#include "src/Logger/ LoggingObserverDriver.h"

#include "Command/Command.h"
#include "CommandProcessing/CommandProcessor.h"
using namespace std;


int main() {
    testPlayerStrategies();
	
	CommandProcessor command_processor = CommandProcessor();
    GameEngine game = GameEngine();

    Command *command = command_processor.getCommand(&game);
    TournamentSetup tournament_setup = command_processor.getTournamentSetupFromCommand(command);
    return 0;
}
