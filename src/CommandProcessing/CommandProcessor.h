//
// Created by manol on 10/15/2024.
//

#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H
#include <fstream>
#include "../GameEngine/GameEngine.h"
#include "../Command/Command.h"
#include <vector>


class GameEngine;

class CommandProcessor {
    private:
        virtual Command* readCommand();
        void saveCommand(Command* command);
        void validate(GameEngine* gameEngine, Command* command);
        vector<Command*> commands;
    protected:
        Command* getCommandFromString(string commandString);
        friend class GameEngine;
    public:
        Command* getCommand(GameEngine* gameEngine);
        CommandProcessor();
        CommandProcessor(const CommandProcessor& copy);
        CommandProcessor& operator=(const CommandProcessor& copy);
        friend ostream& operator<<(ostream& os, CommandProcessor& commandProcessor);
        vector<Command*> getCommands() const ;
};

class FileLineReader {
    private:
        string filePath;
        int currentLine;
    public:
        explicit FileLineReader(string filePath);
        string readLineFromFile();
};

class FileCommandProcessorAdapter : public CommandProcessor {
    private:
        Command* readCommand() override;
        FileLineReader* fileLineReader;
    public:
        explicit FileCommandProcessorAdapter(string filePath);
};
#endif //COMMANDPROCESSING_H
