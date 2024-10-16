//
// Created by manol on 10/15/2024.
//

#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H
#include <GameEngine.h>
#include <vector>

#include "Command/Command.h"


class CommandProcessor {
    private:
        Command* readCommand();
        void saveCommand(Command* command);
        void validate(GameEngine* gameEngine, Command* command);
        vector<Command*> commands;
    public:
        Command* getCommand(GameEngine* gameEngine);

};



#endif //COMMANDPROCESSING_H
