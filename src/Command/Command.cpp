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

Command::Command(const Command &command) {
    this->command = command.command;
    this->type = command.type;
    this->success = command.success;
    this->effect = command.effect;
}

Command &Command::operator=(const Command &other) {
    if (this != &other) {
        this->command = other.command;
        this->type = other.type;
        this->success = other.success;
        this->effect = other.effect;
    }

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Command &command) {
    os << command.command;
    return os;
}



