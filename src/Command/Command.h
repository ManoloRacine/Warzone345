//
// Created by manol on 10/15/2024.
//

#ifndef COMMAND_H
#define COMMAND_H

#include "../GameEngine/GameEngine.h"
#include "../Logger/LogObserver.h"
#include <iostream>
#include <sstream>
using namespace std;

class GameEngine;
class ILogObserver;

enum CommandType {
    LoadMap,
    ValidateMap,
    AddPlayer,
    GameStart,
    Replay,
    Quit,
    Invalid
};

//Loggable class with string to log
class Command: public Subject, ILoggable {
    private:
        string command;
        string effect;
        bool success;
        CommandType type;
        GameEngine* game = nullptr;
    public:
        Command(string command, CommandType type);
        Command(string command, CommandType type, GameEngine* game);
        Command(const Command& command);
        Command& operator=(const Command& command);
        friend ostream& operator<<(ostream& os, const Command& command);
        string getCommand();
        CommandType getType();
        void setSuccess(bool success);
        bool getSuccess();
        void saveEffect(string effect);
        string getEffect();
        // Logging
        std::string stringToLog() override;

};
#endif //COMMAND_H
