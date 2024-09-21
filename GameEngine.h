//
// Created by manol on 9/21/2024.
//

#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <string>

using namespace std;

class GameEngine;

class GameEngineState {
    public:
    virtual void changeState(GameEngine* game_engine, string state_input);
    virtual string getName();
};

class StartState : public GameEngineState {
    public:
    void changeState(GameEngine* game_engine, string state_input);
    static GameEngineState& getInstance();
    string getName();
};

class MapLoadedState : public GameEngineState {
    public:
    void changeState(GameEngine* game_engine, string state_input);
    static GameEngineState& getInstance();
    string getName();

};

class GameEngine {


    public:
    GameEngine();
    GameEngineState* getCurrentState() const {return gameEngineState;}
    void setState(GameEngineState& new_state);
    void changeState(string state_input);

    private:
    GameEngineState* gameEngineState;

};



#endif //GAMEENGINE_H
