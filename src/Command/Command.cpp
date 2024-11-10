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
Command::Command(string command, CommandType commandType, GameEngine* game) {
    this->command = std::move(command);
    this->type = commandType;
    this->success = false;
    this->game = game;
    Subject::attach((ILogObserver*)game->logObserver);
}
void Command::saveEffect(string effect) {
    this->effect = std::move(effect);
    Subject::notify(this);
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

string Command::getEffect() {
    return effect;
}

// logging
std::string Command::stringToLog() {
    std::stringstream stream;
    stream << "COMMAND: ";
    stream << "Saved Effect \"";
    stream << getEffect();
    stream << "\""; //quoting
    return stream.str();
}

Command::Command(const Command &command) {
    this->command = command.command;
    this->type = command.type;
    this->success = command.success;
    this->effect = command.effect;
    this->game = command.game;
    if (this->game != nullptr) {Subject::attach((ILogObserver*)game->logObserver);} //subscribing to notifications
}

Command &Command::operator=(const Command &other) {
    if (this != &other) {
        this->command = other.command;
        this->type = other.type;
        this->success = other.success;
        this->effect = other.effect;
        if (this->game != nullptr) {Subject::attach((ILogObserver*)game->logObserver);} //subscribing to notifications
    }

    return *this;
}

std::ostream &operator<<(std::ostream &os, const Command &command) {
    os << command.command;
    return os;
}



