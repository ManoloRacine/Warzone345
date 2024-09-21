#include <iostream>

#define quote(x) #x

#include "GameEngine.h"
using namespace std;

int main() {
    GameEngine game;
    while (true) {
        string input;
        cin >> input;
        game.changeState(input);
        cout << game.getCurrentState()->getName() << endl;
    }
    return 0;
}
