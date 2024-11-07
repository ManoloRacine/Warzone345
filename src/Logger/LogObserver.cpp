//
// Created by Ryad on 2024-11-07.
//

#include "LogObserver.h"

// attach observer to vector to be notified
void Subject::attach(ILogObserver* observer) {
  if(observer == nullptr) {
    throw std::runtime_error("observer is nullptr");
  }
  observers.push_back(observer);
}

// detaching observer the vector
void Subject::detach(ILogObserver* observer) {
  // loop to find him and erase from vector
  for(auto it = observers.begin(); it != observers.end(); it++){
    if(*it == observer){
      observers.erase(it);
      return;
    }
  }
}

// notifying the observers by updating them
void Subject::notify(ILoggable* loggable) {
  // loop through subscribers and notify them
  for(auto& observer : observers){
    observer->update(loggable);
  }
}

// reseting the observers vector
void Subject::resetObservers() {
  this->observers = std::vector<ILogObserver*>();
}


//LogObserver --------------------------------------


// Default constructor
LogObserver::LogObserver(GameEngine* game): game(game)
{
    //there should be a game engine initilized to actually log the game
    if(game == nullptr) {
      throw std::runtime_error("Game Engine is NULL in LogObserver::LogObserver(GameEngine* game)");
    }
}

// copy constructor
LogObserver::LogObserver(LogObserver *observer) {
    this->game = observer->game;
}

// updating commands on the txt file
void LogObserver::update(ILoggable* loggable) {
    std::fstream file;
    try {
        file.open("gamelog.txt", std::fstream::out | std::fstream::app);
        file << loggable->stringToLog();
        file << '\n';
    }
    catch(const std::fstream::failure& e){
        std::cout << "Cannot open/write gamelog.txt" << std::endl;
    }
    file.close();
}

std::ostream& operator << (std::ostream &out, const LogObserver &log)
{
  out << "-LogObserver" << std::endl;
  return out;
}

// assignment operator overriding
LogObserver& LogObserver::operator=(const LogObserver &other){
  if(this == &other){
    return *this;
  }

  this->game = other.game;

  return *this;
}