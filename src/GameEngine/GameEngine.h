//
// Created by manol on 9/21/2024.
//
// FSM pattern referenced from https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/

#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <string>

using namespace std;

class GameEngine;

class GameState {
    public:
    virtual void changeState(GameEngine* game_engine, string state_input) = 0;
    virtual string getName() = 0;
};

class StartState : public GameState {
    public:
    void changeState(GameEngine* game_engine, string state_input) override;
    static GameState& getInstance();
    string getName() override;
};

class MapLoadedState : public GameState {
    public:
    void changeState(GameEngine* game_engine, string state_input) override;
    static GameState& getInstance();
    string getName() override;
};

class MapValidatedState : public GameState {
public:
    void changeState(GameEngine* game_engine, string state_input) override;
    static GameState& getInstance();
    string getName() override;
};

class PlayersAddedState : public GameState {
public:
    void changeState(GameEngine* game_engine, string state_input) override;
    static GameState& getInstance();
    string getName() override;
};

class AssignReinforcementState : public GameState {
public:
    void changeState(GameEngine* game_engine, string state_input) override;
    static GameState& getInstance();
    string getName() override;
};

class IssueOrdersState : public GameState {
public:
    void changeState(GameEngine* game_engine, string state_input) override;
    static GameState& getInstance();
    string getName() override;
};

class ExecuteOrdersState : public GameState {
public:
    void changeState(GameEngine* game_engine, string state_input) override;
    static GameState& getInstance();
    string getName() override;
};

class WinState : public GameState {
public:
    void changeState(GameEngine* game_engine, string state_input) override;
    static GameState& getInstance();
    string getName() override;
};

class GameEngine {
    public:
    GameEngine();
    GameState* getCurrentState() const;
    void setState(GameState& new_state);
    void changeState(string state_input);

    private:
    GameState* gameEngineState;
};



#endif //GAMEENGINE_H
