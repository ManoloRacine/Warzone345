//
// Created by manol on 10/15/2024.
//

#include "CommandProcessor.h"

#include <iostream>
#include <ranges>
#include <string>
using namespace std;

#include <boost/algorithm/string.hpp>
using namespace boost::algorithm;

Command *CommandProcessor::getCommandFromString(string commandString) {
    vector<string> splitCommand;
    split(splitCommand, commandString, is_any_of(" "));

    if (splitCommand.size() == 1) {
        if (splitCommand.at(0) == "validatemap") {
            return new Command(commandString, ValidateMap);
        }
        if (splitCommand.at(0) =="gamestart") {
            return new Command(commandString, GameStart);
        }
        if (splitCommand.at(0) == "replay") {
            return new Command(commandString, Replay);
        }
        if (splitCommand.at(0) == "quit") {
            return new Command(commandString, Quit);
        }
    }
    else if (splitCommand.size() == 2) {
        if (splitCommand.at(0) == "loadmap") {
            return new Command(commandString, LoadMap);
        }
        if (splitCommand.at(0) == "addplayer") {
            return new Command(commandString, AddPlayer);
        }
    }

    return new Command(commandString, Invalid);
}


Command *CommandProcessor::readCommand() {
    string commandString;

    getline(cin, commandString);

    return getCommandFromString(commandString);
}


void CommandProcessor::validate(GameEngine * gameEngine, Command *command) {
    vector<string> splitCommand;
    split(splitCommand, command->getCommand(), is_any_of(" "));

    State currentGameState = gameEngine->getCurrentState()->getState();
    CommandType commandType = command->getType();

    switch (commandType) {
        case ValidateMap:
            if (currentGameState == MapLoaded) {
                command->saveEffect("Map was validated");
                command->setSuccess(true);
                gameEngine->changeState("validatemap");
                return;
            }
        break;
        case GameStart:
            if (currentGameState == PlayersAdded) {
                command->saveEffect("Game was started");
                command->setSuccess(true);
                gameEngine->changeState("gamestart");
                return;
            }
        break;
        case Replay:
            if (currentGameState == Win) {
                command->saveEffect("Replay started");
                command->setSuccess(true);
                gameEngine->changeState("play");
                return;
            }
        break;
        case Quit:
            if (currentGameState == Win) {
                command->saveEffect("Game was ended");
                command->setSuccess(true);
                gameEngine->changeState("end");
                return;
            }
        break;
        case LoadMap:
            if (currentGameState == Start || currentGameState == MapLoaded) {
                command->saveEffect("Map was loaded");
                command->setSuccess(true);
                gameEngine->changeState("loadmap");
                return;
            }
        break;
        case AddPlayer:
            if (currentGameState == MapValidated || currentGameState == PlayersAdded) {
                command->saveEffect("Player was added");
                command->setSuccess(true);
                gameEngine->changeState("addplayer");
                return;
            }
        default:
            throw std::runtime_error("Command not recognized, when it should have been checked previously");

    }

    command->saveEffect("invalid game state for command : " + gameEngine->getCurrentState()->getName());
    command->setSuccess(false);

}

void CommandProcessor::saveCommand(Command* command) {
    commands.push_back(command);
}


Command *CommandProcessor::getCommand(GameEngine *gameEngine) {
    Command* command = readCommand();
    validate(gameEngine,command);
    saveCommand(command);
    return command;
}

Command *FileCommandProcessorAdapter::readCommand() {
    string commandString = fileLineReader->readLineFromFile();

    return getCommandFromString(commandString);
}

string FileLineReader::readLineFromFile() {
    ifstream file(filePath);

    string line;

    int lineBeingRead = 1;

    while (getline(file, line)) {
        if (lineBeingRead == currentLine) {
            currentLine++;
            file.close();
            return line;
        }
        lineBeingRead++;
    }

    file.close();

    //TODO throw error or something
}

FileLineReader::FileLineReader(string filePath) {
    this->filePath = filePath;
    currentLine = 1;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string filePath) {
    fileLineReader = new FileLineReader(filePath);
}







