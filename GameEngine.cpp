//
// Created by manol on 9/21/2024.
//
//FSM pattern referenced from https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/

#include "GameEngine.h"
void StartState::changeState(GameEngine *game_engine, string state_input) {
    if (state_input == "loadmap") {
        game_engine->setState(MapLoadedState::getInstance());
    }
}

string StartState::getName() {
    return "start state";
}


GameEngineState& StartState::getInstance() {
    static StartState instance;
    return instance;
}

void MapLoadedState::changeState(GameEngine *game_engine, string state_input) {
    if (state_input == "start") {
        game_engine->setState(StartState::getInstance());
    }
}

string MapLoadedState::getName() {
    return "map loaded state";
}


GameEngineState& MapLoadedState::getInstance() {
    static MapLoadedState instance;
    return instance;
}

GameEngine::GameEngine() {
    gameEngineState = &StartState::getInstance();
}


void GameEngine::changeState(string state_input) {
    gameEngineState->changeState(this, state_input);
}

void GameEngine::setState(GameEngineState &new_state) {
    gameEngineState = &new_state;
}


