//
// Created by Ryad on 2024-11-07.
//
#include "LogObserver.h"


//------------------------------------------------Subject - (Observable)-------------------------------------


void Subject::getObservers() {
  std::cout << observers[0] << std::endl;
}

void Subject::attach(ILogObserver* observer) {
  if(observer == nullptr){ throw std::runtime_error("Observer is null."); }
  observers.push_back(observer);
}

void Subject::detach(ILogObserver* observer) {
  for(auto it = observers.begin(); it != observers.end(); it++){
    if(*it == observer){
      observers.erase(it);
      return;
    }
  }
}

void Subject::notify(ILoggable* loggable) {
  for(auto& observer : observers){
    observer->update(loggable);
  }
}

void Subject::resetObservers() {
  this->observers = std::vector<ILogObserver*>();
}


//----------------------------------------------------LogObserver-----------------------------------------------------

// Default constructor
LogObserver::LogObserver(GameEngine* game)
        :game(game)
{
    if(game == nullptr){throw std::runtime_error("LogObserver::Error -> game engine undefined/nullptr");}
}
LogObserver::LogObserver(LogObserver *observer) {
    this->game = observer->game;
}

void LogObserver::update(ILoggable* loggable) {
    std::fstream file;
    try {
        file.open("gamelog.txt", std::fstream::out | std::fstream::app);
        file << loggable->stringToLog();
        file << '\n';
    }
    catch(const std::fstream::failure& e){
        std::cout << "cannot open file" << std::endl;
    }
    file.close();
}

std::ostream& operator << (std::ostream &out, const LogObserver &log)
{
  out << "LogObserver" << std::endl;
  return out;
}

LogObserver& LogObserver::operator=(const LogObserver &other){
  if(this == &other){
    return *this;
  }

  this->game = other.game;

  return *this;
}