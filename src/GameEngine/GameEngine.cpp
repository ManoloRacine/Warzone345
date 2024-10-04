//
// Created by manol on 9/21/2024.
//
// FSM pattern referenced from https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/

#include "GameEngine.h"
#include <iostream>
using namespace std;

//Changes current game engine state based on input
void StartState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "loadmap") {
        gameEngine->setState(MapLoadedState::getInstance());
    }
    else {
        cout << "Invalid input" << endl;
    }
}

string StartState::getName() {
    return "start state";
}

//returns a singleton representing this state
GameState& StartState::getInstance() {
    static StartState instance;
    return instance;
}


//Changes current game engine state based on input
void MapLoadedState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "loadmap") {
        gameEngine->setState(MapLoadedState::getInstance());
    }
    else if (stateInput == "validatemap") {
        gameEngine->setState(MapValidatedState::getInstance());
    }
    else {
        cout << "Invalid input" << endl;
    }
}

string MapLoadedState::getName() {
    return "map loaded state";
}

//returns a singleton representing this state
GameState& MapLoadedState::getInstance() {
    static MapLoadedState instance;
    return instance;
}


//Changes current game engine state based on input
void MapValidatedState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "addplayer") {
        gameEngine->setState(PlayersAddedState::getInstance());
    }
    else {
        cout << "Invalid input" << endl;
    }
}

//returns a singleton representing this state
GameState & MapValidatedState::getInstance() {
    static MapValidatedState instance;
    return instance;
}

string MapValidatedState::getName() {
    return "map validated state";
}


//Changes current game engine state based on input
void PlayersAddedState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "addplayer") {
        gameEngine->setState(PlayersAddedState::getInstance());
    }
    else if (stateInput == "assigncountries") {
        gameEngine->setState(AssignReinforcementState::getInstance());
    }
    else {
        cout << "Invalid input" << endl;
    }
}

//returns a singleton representing this state
GameState & PlayersAddedState::getInstance() {
    static PlayersAddedState instance;
    return instance;
}

string PlayersAddedState::getName() {
    return "players added state";
}


//Changes current game engine state based on input
void AssignReinforcementState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "issueorder") {
        gameEngine->setState(IssueOrdersState::getInstance());
    }
    else {
        cout << "Invalid input" << endl;
    }
}

//returns a singleton representing this state
GameState & AssignReinforcementState::getInstance() {
    static AssignReinforcementState instance;
    return instance;
}

string AssignReinforcementState::getName() {
    return "assign reinforcement";
}


//Changes current game engine state based on input
void IssueOrdersState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "issueorder") {
        gameEngine->setState(IssueOrdersState::getInstance());
    }
    else if (stateInput == "endissueorders") {
        gameEngine->setState(ExecuteOrdersState::getInstance());
    }
    else {
        cout << "Invalid input" << endl;
    }
}

//returns a singleton representing this state
GameState & IssueOrdersState::getInstance() {
    static IssueOrdersState instance;
    return instance;
}

string IssueOrdersState::getName() {
    return "issue orders";
}


//Changes current game engine state based on input
void ExecuteOrdersState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "execorder") {
        gameEngine->setState(ExecuteOrdersState::getInstance());
    }
    else if (stateInput == "endexecorders") {
        gameEngine->setState(AssignReinforcementState::getInstance());
    }
    else if (stateInput == "win") {
        gameEngine->setState(WinState::getInstance());
    }
    else {
        cout << "Invalid input" << endl;
    }
}

//returns a singleton representing this state
GameState & ExecuteOrdersState::getInstance() {
    static ExecuteOrdersState instance;
    return instance;
}

string ExecuteOrdersState::getName() {
    return "execute orders";
}


//Changes current game engine state based on input
void WinState::changeState(GameEngine *gameEngine, string stateInput) {
    if (stateInput == "play") {
        gameEngine->setState(StartState::getInstance());
    }
    else if (stateInput == "end") {
        exit(0);
    }
    else {
        cout << "Invalid input" << endl;
    }
}

//returns a singleton representing this state
GameState & WinState::getInstance() {
    static WinState instance;
    return instance;
}

string WinState::getName() {
    return "win";
}



GameEngine::GameEngine() {
    gameEngineState = &StartState::getInstance();
}

GameState* GameEngine::getCurrentState() const {
    return gameEngineState;
}

void GameEngine::changeState(string stateInput) {
    gameEngineState->changeState(this, stateInput);
}

void GameEngine::setState(GameState &newState) {
    gameEngineState = &newState;
}

GameEngine::GameEngine(const GameEngine &gameEngine) {
    gameEngineState = gameEngine.gameEngineState;
}

GameEngine & GameEngine::operator=(const GameEngine &other) {
    if (this != &other) {
        gameEngineState = other.gameEngineState;
    }

    return *this;
}

std::ostream & operator<<(std::ostream &os, const GameEngine &gameEngine) {
    os << gameEngine.getCurrentState()->getName();
    return os;
}

