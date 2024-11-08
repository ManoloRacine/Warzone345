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
#include "../Cards/Cards.h"

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
protected:
    State state;

    GameState(State state);
};

class StartState : public GameState {
    public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    StartState();
};

class MapLoadedState : public GameState {
    public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    MapLoadedState();
};

class MapValidatedState : public GameState {
public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    MapValidatedState();
};

class PlayersAddedState : public GameState {
public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    PlayersAddedState();
};

class AssignReinforcementState : public GameState {
public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    AssignReinforcementState();
};

class IssueOrdersState : public GameState {
public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    IssueOrdersState();
};

class ExecuteOrdersState : public GameState {
public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    ExecuteOrdersState();
};

class WinState : public GameState {
public:
    void changeState(GameEngine* gameEngine, string stateInput) override;
    static GameState& getInstance();
    string getName() override;
private:
    WinState();
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

    //------------- A2-P2 CHANGES --------------- ( by Nektarios )
    void startupPhase(); //A2-Part2
    vector<Player*> playerList; // ( we need to store players somewhere)
    void assignTerritoriesToPlayers(Map& map, std::vector<Player*>& players);
    void determineOrderOfPlay(std::vector<Player*>& players);
    void setReinforcementPools(std::vector<Player*>& players);
    Map * gameMap; // Also need a map object
    inline void setMap(Map& map) { this->gameMap = &map; };
    Deck * gameDeck;
    void draw2cards(std::vector<Player*>& players);
    void printAllMaps(const std::string& mapDirectory);
    //---------------------------------------

    //------------- A2-P3 CHANGES -------------- ( by Griffin)
    void reinforcementPhase(std::vector<Player*>& players, std::vector<Continent*>& continents);
    void issueOrdersPhase(Map& map, std::vector<Player*>& players);
    void resetPlayerStatuses(std::vector<Player*>& players);
    Territory* getTerritoriesByName(Map& map, string territory);
    Player* getPlayerByName(std::vector<Player*>& players, string targetPlayer);
   


    private:
    GameState* gameEngineState;
};

#endif //GAMEENGINE_H
