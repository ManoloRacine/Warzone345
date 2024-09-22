//
// Created by manol on 9/21/2024.
//

#include "GameEngine.h"
#include <iostream>
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
