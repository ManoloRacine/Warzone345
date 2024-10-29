//
// Created by manol on 10/15/2024.
//

#include "CommandProcessor.h"
#include <iostream>
#include <sstream>  // For std::istringstream
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Custom split function to replace boost::algorithm::split
void split(vector<string>& result, const string& input, const char delimiter = ' ') {
    result.clear();
    istringstream stream(input);
    string token;
    while (getline(stream, token, delimiter)) {
        if (!token.empty()) {
            result.push_back(token);
        }
    }
}

// Function to convert a string to lowercase
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char c) {
        return tolower(c);
    });
    return lowerStr;
}

Command *CommandProcessor::getCommandFromString(string commandString) {
    vector<string> splitCommand;
    commandString = toLower(commandString);
    split(splitCommand, commandString, ' ');

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
    commandString = toLower(commandString);
    return getCommandFromString(commandString);
}

void CommandProcessor::validate(GameEngine * gameEngine, Command *command) {
    vector<string> splitCommand;
    split(splitCommand, command->getCommand(), ' ');
    State currentGameState = gameEngine->getCurrentState()->getState();
    CommandType commandType = command->getType();
    bool commandValid = false;

    switch (commandType) {
        case ValidateMap:
            if (currentGameState == MapLoaded) {
                command->saveEffect("Map was validated");
                commandValid = true;
                gameEngine->changeState("validatemap");
            }
            break;

        case GameStart:
            if (currentGameState == PlayersAdded) {
                command->saveEffect("Game was started");
                commandValid = true;
                gameEngine->changeState("gamestart");
            }
            break;

        case Replay:
            if (currentGameState == Win) {
                command->saveEffect("Replay started");
                commandValid = true;
                gameEngine->changeState("play");
            }
            break;

        case Quit:
            if (currentGameState == Win) {
                command->saveEffect("Game was ended");
                commandValid = true;
                gameEngine->changeState("end");
            }
            break;

        case LoadMap:
            if (currentGameState == Start || currentGameState == MapLoaded) {
                command->saveEffect("Map was loaded");
                commandValid = true;
                gameEngine->changeState("loadmap");
            }
            break;

        case AddPlayer:
            if (currentGameState == MapValidated || currentGameState == PlayersAdded) {
                command->saveEffect("Player was added");
                commandValid = true;
                gameEngine->changeState("addplayer");
            }
            break;

        default:
            throw std::runtime_error("Command not recognized: " + std::to_string(commandType));
    }

    // Handle command validity
    if (!commandValid) {
        command->saveEffect("Invalid game state for command: " + gameEngine->getCurrentState()->getName());
        command->setSuccess(false);
    } else {
        command->setSuccess(true);
    }
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
    // TODO throw error or something

    return 0;
}

FileLineReader::FileLineReader(string filePath) {
    this->filePath = filePath;
    currentLine = 1;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string filePath) {
    fileLineReader = new FileLineReader(filePath);
}

