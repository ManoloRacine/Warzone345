//
// Created by manol on 10/15/2024.
//

#ifndef COMMAND_H
#define COMMAND_H
#include <string>
using namespace std;

enum CommandType {
    LoadMap,
    ValidateMap,
    AddPlayer,
    GameStart,
    Replay,
    Quit,
    Invalid
};

class Command {
    private:
        string command;
        string effect;
        bool success;
        CommandType type;
    public:
        Command(string command, CommandType type);
        string getCommand();
        CommandType getType();
        void setSuccess(bool success);
        void saveEffect(string effect);

};



#endif //COMMAND_H
