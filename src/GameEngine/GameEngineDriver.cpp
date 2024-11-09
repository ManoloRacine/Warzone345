//
// Created by manol on 9/21/2024.
//

#include "GameEngine.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

void testGameStates(){
    GameEngine game;
    while (true) {
        string input;
        cout << "current state : " << game.getCurrentState()->getName() << endl;
        cout << "enter the next state you want to go to" << endl;
        cin >> input;
        game.changeState(input);
    }
}


// Function to simulate the startup phase of the game
void testStartupPhase() {
    GameEngine game; // Initialize the GameEngine
        // Check current state after commands
    game.startupPhase();
}



void testReinforcementPhase() {
    GameEngine game;
    MapLoader mapLoader;
    Map loadedMap;
    mapLoader.loadMap(loadedMap,"../res/maps/usa.txt");
    cout << "loadingMap: usa.txt..." << endl;
    game.gameMap = new Map(loadedMap);
    bool result = loadedMap.validate();
    cout << "Map validation is: " << result << endl;
    Player* player1 = new Player("bob");
    game.playerList.push_back(player1);
    cout << "adding player bob" << endl;
    Player* player2 = new Player("sam");
    game.playerList.push_back(player2);
    cout << "adding player sam" << endl;
    cout << "Assigning territories" << endl;
    game.assignTerritoriesToPlayers(loadedMap, game.playerList);
    cout << "Setting Reinforcement pools" << endl;
    game.setReinforcementPools(game.playerList);
    game.draw2cards(game.playerList);
    cout << *player1 << endl;
    cout << *player2 << endl;

    Deploy *deployOrder = new Deploy(player1, player2, 4, nullptr, game.getTerritoryByName(loadedMap, "Detroit"));

    player1->issueOrder(deployOrder);

    cout<<"Order type is: " << *(player1->getOrdersList()->getList()[0]) << endl;

}
