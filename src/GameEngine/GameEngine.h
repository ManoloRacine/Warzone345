//
// Created by manol on 9/21/2024.
//
// FSM pattern referenced from https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/

#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <string>
#include "../Command/Command.h"
#include "../CommandProcessing/CommandProcessor.h"
#include "../Map/Map.h"

using namespace std;

// Forward declaration
class GameEngine;


enum State {
    Start,
    MapLoaded,
    MapValidated,
    PlayersAdded,
    AssignReinforcement,
    IssueOrders,
    ExecuteOrders,
    Win
};

class GameState {
    public:
    virtual void changeState(GameEngine* gameEngine, string stateInput) = 0;
    virtual string getName() = 0;
    State getState();
private:
    State state;
};

class StartState : public GameState {
    public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    State state = Start;
};

class MapLoadedState : public GameState {
    public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    State state = MapLoaded;
};

class MapValidatedState : public GameState {
public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    State state = MapValidated;
};

class PlayersAddedState : public GameState {
public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    State state = PlayersAdded;
};

class AssignReinforcementState : public GameState {
public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    State state = AssignReinforcement;
};

class IssueOrdersState : public GameState {
public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    State state = IssueOrders;
};

class ExecuteOrdersState : public GameState {
public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    State state = ExecuteOrders;
};

class WinState : public GameState {
public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    State state = Win;
};

class GameEngine {
    public:
    GameEngine();
    GameState* getCurrentState() const;
    void setState(GameState& newState);
    void changeState(string stateInput);
    GameEngine(const GameEngine& gameEngine);
    GameEngine& operator=(const GameEngine& gameEngine);
    friend std::ostream& operator<<(std::ostream& os, const GameEngine& gameEngine);

    void startupPhase(); //A2-Part2
    vector<string> getTxtFiles(const string& directoryPath); //A2-Part2
    vector<Player*> playerList; //A2-Part2 ( we need to store players somewhere)
    void assignTerritoriesToPlayers(Map& map, std::vector<Player*>& players); //A2-Part2

    private:
    GameState* gameEngineState;
};

#endif //GAMEENGINE_H
