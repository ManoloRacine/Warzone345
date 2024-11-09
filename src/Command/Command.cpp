//
// Created by manol on 10/15/2024.
//

#include "Command.h"

#include <utility>


Command::Command(string command, CommandType commandType) {
    this->command = std::move(command);
    this->type = commandType;
    this->success = false;
}

void Command::saveEffect(string effect) {
    this->effect = std::move(effect);
}

CommandType Command::getType() {
    return type;
}

void Command::setSuccess(bool success) {
    this->success = success;
}

bool Command::getSuccess() {
    return success;
}

string Command::getCommand() {
    return command;
}


