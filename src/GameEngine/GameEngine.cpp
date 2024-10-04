//
// Created by manol on 9/21/2024.
//
// FSM pattern referenced from https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/

#include "GameEngine.h"
#include <iostream>
using namespace std;

void StartState::changeState(GameEngine *game_engine, string state_input) {
    if (state_input == "loadmap") {
        game_engine->setState(MapLoadedState::getInstance());
    }
    else {
        cout << "Invalid input" << endl;
    }
}

string StartState::getName() {
    return "start state";
}

GameState& StartState::getInstance() {
    static StartState instance;
    return instance;
}


void MapLoadedState::changeState(GameEngine *game_engine, string state_input) {
    if (state_input == "loadmap") {
        game_engine->setState(MapLoadedState::getInstance());
    }
    else if (state_input == "validatemap") {
        game_engine->setState(MapValidatedState::getInstance());
    }
    else {
        cout << "Invalid input" << endl;
    }
}

string MapLoadedState::getName() {
    return "map loaded state";
}

GameState& MapLoadedState::getInstance() {
    static MapLoadedState instance;
    return instance;
}

void MapValidatedState::changeState(GameEngine *game_engine, string state_input) {
    if (state_input == "addplayer") {
        game_engine->setState(PlayersAddedState::getInstance());
    }
    else {
        cout << "Invalid input" << endl;
    }
}

GameState & MapValidatedState::getInstance() {
    static MapValidatedState instance;
    return instance;
}

string MapValidatedState::getName() {
    return "map validated state";
}

void PlayersAddedState::changeState(GameEngine *game_engine, string state_input) {
    if (state_input == "addplayer") {
        game_engine->setState(PlayersAddedState::getInstance());
    }
    else if (state_input == "assigncountries") {
        game_engine->setState(AssignReinforcementState::getInstance());
    }
    else {
        cout << "Invalid input" << endl;
    }
}

GameState & PlayersAddedState::getInstance() {
    static PlayersAddedState instance;
    return instance;
}

string PlayersAddedState::getName() {
    return "players added state";
}

void AssignReinforcementState::changeState(GameEngine *game_engine, string state_input) {
    if (state_input == "issueorder") {
        game_engine->setState(IssueOrdersState::getInstance());
    }
    else {
        cout << "Invalid input" << endl;
    }
}

GameState & AssignReinforcementState::getInstance() {
    static AssignReinforcementState instance;
    return instance;
}

string AssignReinforcementState::getName() {
    return "assign reinforcement";
}

void IssueOrdersState::changeState(GameEngine *game_engine, string state_input) {
    if (state_input == "issueorder") {
        game_engine->setState(IssueOrdersState::getInstance());
    }
    else if (state_input == "endissueorders") {
        game_engine->setState(ExecuteOrdersState::getInstance());
    }
    else {
        cout << "Invalid input" << endl;
    }
}

GameState & IssueOrdersState::getInstance() {
    static IssueOrdersState instance;
    return instance;
}

string IssueOrdersState::getName() {
    return "issue orders";
}

void ExecuteOrdersState::changeState(GameEngine *game_engine, string state_input) {
    if (state_input == "execorder") {
        game_engine->setState(ExecuteOrdersState::getInstance());
    }
    else if (state_input == "endexecorders") {
        game_engine->setState(AssignReinforcementState::getInstance());
    }
    else if (state_input == "win") {
        game_engine->setState(WinState::getInstance());
    }
    else {
        cout << "Invalid input" << endl;
    }
}

GameState & ExecuteOrdersState::getInstance() {
    static ExecuteOrdersState instance;
    return instance;
}

string ExecuteOrdersState::getName() {
    return "execute orders";
}

void WinState::changeState(GameEngine *game_engine, string state_input) {
    if (state_input == "play") {
        game_engine->setState(StartState::getInstance());
    }
    else if (state_input == "end") {
        exit(0);
    }
    else {
        cout << "Invalid input" << endl;
    }
}

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

void GameEngine::changeState(string state_input) {
    gameEngineState->changeState(this, state_input);
}

void GameEngine::setState(GameState &new_state) {
    gameEngineState = &new_state;
}

