//
// Created by Nektarios on 11/30/2024.
//

#include "TournamentDriver.h"
#include "GameEngine.h"




void testTournament(GameEngine game,CommandProcessor commandProcessor, TournamentSetup tournamentSetup) {

    const int gameCount = tournamentSetup.nbGames;
    const int turnCount = tournamentSetup.nbTurns;


    game.GameEngine::startUpPhase(commandProcessor,tournamentSetup.mapNames,tournamentSetup.playerStrategies);

    int mapCount = game.gameMaps.size();

    for ( int i = 0 ; i < mapCount; i++ ) {

        game.gameMap = game.gameMaps[mapCount];

        for ( int j = 0 ; j < gameCount; j++) {
            game.startGame();
            tournamentPlay(game,*game.gameMap,turnCount);
            game.resetGame();
        }
    }

}


void tournamentPlay(GameEngine game, Map loadedMap, int maxTurnCount) {
    bool play = true;
    int currentTurns = 0;
    while (play) {

        cout << "Tournament Game Starting..." << endl;

        game.resetPlayerStatuses(game.playerList, game.gameDeck);
        cout << "PLAYER RESET" << endl;

        game.reinforcementPhase(loadedMap, game.playerList);
        cout << "END OF REINFORCEMENT" << endl;

        game.issueOrdersPhase(loadedMap, game.playerList);
        cout << "END OF ISSUE ORDERS" << endl;

        game.orderExecutionPhase(game.playerList);
        cout << "END OF ORDER EXECUTION" << endl;

        currentTurns++;

        if (game.playerList.size() <= 1) {
            cout << game.playerList[0]->getName() << " wins the game"<< endl;
            play = false;
        } else if (currentTurns >= maxTurnCount )
            cout << " Game exceeded max number of turns, it's a draw" << endl;
            play = false;

    }
}

