//
// Created by Nektarios on 11/30/2024.
//

#include "TournamentDriver.h"
#include "GameEngine.h"
#include <iomanip> // For setw()




void testTournament(GameEngine & game,CommandProcessor & commandProcessor, TournamentSetup tournamentSetup) {

    vector<string> winners = {};

    const int gameCount = tournamentSetup.nbGames;
    const int turnCount = tournamentSetup.nbTurns;


    game.GameEngine::startUpPhase(commandProcessor,tournamentSetup.mapNames,tournamentSetup.playerStrategies);

    int mapCount = game.gameMaps.size();

    for ( int i = 0 ; i < mapCount; i++ ) {

        game.gameMap = game.gameMaps[i];

        for (int j = 0 ; j < gameCount; j++) {

            game.startGame();
            tournamentPlay(game,turnCount,winners);
            game.resetGame();
        }
    }

    cout << endl;
    cout << endl;
    printMode(tournamentSetup);
    printVictory(mapCount,gameCount,winners);
    cout << " Thank you! " << endl;

}


void tournamentPlay(GameEngine & game, int maxTurnCount, vector<string>& winners) {

    vector<Player*> gameList;

    for (auto player : game.playerList) {
        gameList.push_back(player);
    }

    bool play = true;
    int currentTurns = 0;
    while (play) {
        cout << "Tournament Game Turn: " << currentTurns << endl;


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
            cout << gameList[0]->getStrategy() << " wins the game"<< endl;
            string winner = gameList[0]->getStrategy();
            winners.push_back(winner);
            cout << "                                   ----------------------------------------" << endl;
            cout << "                                   -----------------GAME OVER--------------" << endl;
            cout << "                                   ----------------------------------------" << endl;
            play = false;
        } else if (currentTurns >= maxTurnCount ) {
            cout << " Game exceeded max number of turns, it's a draw" << endl;
            winners.emplace_back("draw");
            play = false;
        }
    }
        gameList.clear();
}

void printMode(const TournamentSetup &tournamentSetup) {
    cout << "Tournament mode: " << endl;

    // Print map names
    cout << "M: ";
    for (size_t i = 0; i < tournamentSetup.mapNames.size(); ++i) {
        cout << tournamentSetup.mapNames[i];
        if (i < tournamentSetup.mapNames.size() - 1) { // Add comma only if it's not the last element
            cout << ", ";
        }
    }

    // Print player strategies
    cout << "\nP: ";
    for (size_t i = 0; i < tournamentSetup.playerStrategies.size(); ++i) {
        cout << tournamentSetup.playerStrategies[i];
        if (i < tournamentSetup.playerStrategies.size() - 1) { // Add comma only if it's not the last element
            cout << ", ";
        }
    }

    // Print number of games and turns
    cout << "\nG: " << tournamentSetup.nbGames;
    cout << "\nD: " << tournamentSetup.nbTurns;

    cout << endl;
    cout << endl;
}


void printVictory(int nbMaps, int nbGames, vector<string>& winners) {
    // Print header
    cout << "Results:\n";
    cout << setw(10) << " " << " ";
    for (int game = 1; game <= nbGames; ++game) {
        cout << setw(10) << "Game " + to_string(game);
    }
    cout << endl;

    // Print results per map
    for (int map = 0; map < nbMaps; ++map) {
        cout << setw(10) << "Map " + to_string(map + 1) << " ";
        for (int game = 0; game < nbGames; ++game) {
            cout << setw(10) << winners[map * nbGames + game];
        }
        cout << endl;
    }
}