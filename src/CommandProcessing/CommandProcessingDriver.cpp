//
// Created by manol on 11/8/2024.
//
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
#include "CommandProcessor.h"
#include "GameEngine.h"

void testCommandProcessor() {
    GameEngine* gameEngine = new GameEngine();
    CommandProcessor* fileCommandProcessor = new FileCommandProcessorAdapter("../res/CommandFiles/test.txt");

    try {
          while (true) {
              Command* command = fileCommandProcessor->getCommand(gameEngine);
              cout << "command read from file : " << command->getCommand() << endl;
          }
    }
    catch (const exception& e) {
        printf("%s\n", e.what());
    }

    GameEngine* gameEngine2 = new GameEngine();
    CommandProcessor* commandProcessor = new CommandProcessor();

    while (true) {
        cout << "manually enter a command : ";
        Command* command = commandProcessor->getCommand(gameEngine2);
        if (command->getSuccess()) {
            cout << "command was successful : " << command->getCommand() << endl;

            if (command->getType() == GameStart) {
                break;
            }
        }
        else {
            cout << "command was invalid : " << command->getCommand() << endl;
        }
    }
}
