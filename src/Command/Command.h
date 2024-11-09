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
        Command(const Command& command);
        Command& operator=(const Command& command);
        friend ostream& operator<<(ostream& os, const Command& command);
        string getCommand();
        CommandType getType();
        void setSuccess(bool success);
        bool getSuccess();
        void saveEffect(string effect);

};
#endif //COMMAND_H
