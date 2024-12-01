//
// Created by Nektarios on 11/30/2024.
//

#include "TournamentDriver.h"
#include "GameEngine.h"




void testTournament(GameEngine & game,CommandProcessor & commandProcessor, TournamentSetup tournamentSetup) {

    const int gameCount = tournamentSetup.nbGames;
    const int turnCount = tournamentSetup.nbTurns;


    game.GameEngine::startUpPhase(commandProcessor,tournamentSetup.mapNames,tournamentSetup.playerStrategies);

    int mapCount = game.gameMaps.size();

    for ( int i = 0 ; i < mapCount; i++ ) {

        game.gameMap = game.gameMaps[i];

        for (int j = 0 ; j < gameCount; j++) {
            game.startGame();
            tournamentPlay(game,turnCount);
            game.resetGame();
        }
    }

}


void tournamentPlay(GameEngine & game, int maxTurnCount) {

    vector<Player*> gameList;

    for (auto player : game.playerList) {
        gameList.push_back(player);
    }
    cout << "PlayerList SIZE: "<< game.playerList.size() << endl;

    cout << "Game List SIZE: "<< gameList.size() << endl;

    bool play = true;
    int currentTurns = 0;
    while (play) {
        cout << "Tournament Game Starting..." << endl;

        game.resetPlayerStatuses(gameList, game.gameDeck);
        cout << "PLAYER RESET" << endl;

        if ( currentTurns >= 1 ) {
            game.reinforcementPhase(*game.gameMap, gameList);
            cout << "END OF REINFORCEMENT" << endl;
        }

        game.issueOrdersPhase(*game.gameMap, gameList);
        cout << "END OF ISSUE ORDERS" << endl;

        game.orderExecutionPhase(gameList);
        cout << "END OF ORDER EXECUTION" << endl;

        currentTurns++;

        if (gameList.size() == 1) {
            cout << gameList[0]->getName() << " wins the game"<< endl;
            cout << "                                                     -----------------GAME OVER--------------" << endl;
            play = false;
        } else if (currentTurns >= maxTurnCount ) {
            cout << " Game exceeded max number of turns, it's a draw" << endl;
            play = false;
        }
    }
        gameList.clear();
}

