//
// Created by manol on 10/15/2024.
//

#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include <iostream>
#include <sstream>
#include <vector>
#include "../Logger/LogObserver.h"
#include "../Command/Command.h"
using namespace std;
class Command;

struct TournamentSetup {
    vector<string> mapNames;
    vector<string> playerStrategies;
    int nbGames;
    int nbTurns;
};

// loggable
class CommandProcessor: public Subject, ILoggable {
    private:
        GameEngine* gameEngine;
        virtual Command* readCommand();
        void saveCommand(Command* command);
        void validate(GameEngine* gameEngine, Command* command);
        bool isValidTournamentCommand(string commandString);
        vector<Command*> commands;
    protected:
        Command* getCommandFromString(string commandString);
        friend class GameEngine;
    public:
        Command* getCommand(GameEngine* gameEngine);
        CommandProcessor();

        explicit CommandProcessor(GameEngine* gameEngine);
        CommandProcessor(const CommandProcessor &copy, GameEngine* game);
        CommandProcessor(const CommandProcessor& copy);
        CommandProcessor& operator=(const CommandProcessor& copy);
        friend ostream& operator<<(ostream& os, CommandProcessor& commandProcessor);
        vector<Command*> getCommands() const ;
        // Logging -- A2 - P5
        std::string stringToLog() override;

        //A3-P2
        TournamentSetup getTournamentSetupFromCommand(Command* command);
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
