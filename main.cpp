#include "src/Map/MapDriver.h"
#include "src/Cards/CardsDriver.h"
#include "src/GameEngine/GameEngineDriver.h"
#include "src/Orders/OrderDriver.h"
#include "src/Player/PlayerDriver.h"
#include "src/Player/PlayerStrategiesDriver.h"
#include <iostream>
#include "src/CommandProcessing/CommandProcessingDriver.h"
#include "src/Logger/ LoggingObserverDriver.h"
#include "src/GameEngine/TournamentDriver.h"
#include "Command/Command.h"
#include "CommandProcessing/CommandProcessor.h"
using namespace std;


int main() {
    //testPlayerStrategies();

	CommandProcessor commandProcessor = CommandProcessor();
    GameEngine game = GameEngine();

    string commandString = "tournament -m smallAfrica.txt -p benevolent -p aggressive  -g 3 -d 10";
    Command *command = commandProcessor.getCommandFromString(commandString);
    TournamentSetup tournamentSetup = commandProcessor.getTournamentSetupFromCommand(command);

    testTournament(game,commandProcessor,tournamentSetup);
    return 0;
}
