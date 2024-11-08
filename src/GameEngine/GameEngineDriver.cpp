//
// Created by manol on 9/21/2024.
//

#include "GameEngine.h"
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

